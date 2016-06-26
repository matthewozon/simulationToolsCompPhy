//VTK code deeply inspired by the examples:
    //http://www.vtk.org/Wiki/VTK/Examples/Cxx/Filtering/CombinePolyData
    //http://www.vtk.org/Wiki/VTK/Examples/Cxx/Utilities/AnimationScene
//I thanks the authors of thoses examples that were really helpfull.

//this code is a simple example of how to simulate interaction between two objects (proportional to the distance) and show the result in an animated scene
//Only one mapper and actor are used. The appendPolyData gather the objects to be rendered

//note to my future self: use a vector of objects whose interaction are given by the library compPhy

#include <vtkSmartPointer.h>
#include <vtkAnimationCue.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkCommand.h>
#include <vtkAnimationScene.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCleanPolyData.h>
#include <vtkAppendPolyData.h>
 
//the class that implements the callback functions
class sceneCalculator
{
public:
    //ctor scene calculator
    sceneCalculator()
    {
        //set all objects to 0
        this->SphereSource=0;
        this->SphereSource2=0;

        this->input1=0;
        this->input2=0;

        this->appendFilter=0;

        //set the object containing the whole scene to 0
        this->cleanFilter=0;

        //set the mapper and actor to 0
        this->Mapper=0;
        this->Actor=0;


    }

    //dtor scene calculator
    ~sceneCalculator()
    {
        this->Cleanup();
    }

    //init the scene
    //void StartCue(vtkAnimationCue::AnimationCueInfo *vtkNotUsed(info), vtkRenderer *ren)
    void initScene(vtkAnimationCue::AnimationCueInfo *vtkNotUsed(info), vtkRenderer *ren)
    {
        //the time sampling
        this->dt=0.1;
        this->alpha=0.005;
        this->m1=100.0; this->m2=1.0;

        //the objects
        this->SphereSource=vtkSphereSource::New();
        this->SphereSource->SetRadius(0.02);
        this->x1=-0.025; this->y1=0.0; this->z1=-0.05;
        this->vx1=0.0; this->vy1=0.0; this->vz1=0.0;
        this->SphereSource->SetCenter(this->x1,this->y1,this->z1);

        this->SphereSource2=vtkSphereSource::New();
        this->SphereSource2->SetRadius(0.005);
        this->x2=0.025; this->y2=0.0; this->z2=-0.05;
        this->vx2=0.0; this->vy2=-0.010; this->vz2=0.0;
        this->SphereSource2->SetCenter(this->x2,this->y2,this->z2);

        //new version
        appendFilter = vtkAppendPolyData::New();
        input1 = vtkPolyData::New();
        input1->ShallowCopy(this->SphereSource->GetOutput());
        input2 = vtkPolyData::New();
        input2->ShallowCopy(this->SphereSource2->GetOutput());

        appendFilter->AddInputData(input1);
        appendFilter->AddInputData(input2);
        appendFilter->Update();


        // Remove any duplicate points.
        this->cleanFilter = vtkCleanPolyData::New();
        this->cleanFilter->SetInputConnection(appendFilter->GetOutputPort());
        this->cleanFilter->Update();

        this->Mapper=vtkPolyDataMapper::New();
        this->Mapper->SetInputConnection(cleanFilter->GetOutputPort());

        this->Actor=vtkActor::New();
        this->Actor->SetMapper(this->Mapper);

        ren->AddActor(this->Actor);

        ren->ResetCamera();
        ren->Render();
    }
 
    void updateObjectsPosition(vtkAnimationCue::AnimationCueInfo *vtkNotUsed(info),vtkRenderer *ren)
    {
        //calculate new position of the objects
        double dist=sqrt( (this->x1-this->x2)*(this->x1-this->x2) + (this->y1-this->y2)*(this->y1-this->y2) + (this->z1-this->z2)*(this->z1-this->z2) );
        //cout << "distnace: " << dist << endl;
        //cout << "dt = " << this->dt << endl;
        double F21x=-this->alpha*this->m1*this->m2*(this->x1-this->x2);//*dist;//(dist*dist*dist);
        double F21y=-this->alpha*this->m1*this->m2*(this->y1-this->y2);//*dist;//(dist*dist*dist);
        double F21z=-this->alpha*this->m1*this->m2*(this->z1-this->z2);//*dist;//(dist*dist*dist);
        //cout << "interaction 2->1: (" << F21x << "," << F21y << "," << F21z << ")" << endl;

        //update position
        this->x1+=this->dt*this->vx1;   this->y1+=this->dt*this->vy1;   this->z1+=this->dt*this->vz1;
        this->x2+=this->dt*this->vx2;   this->y2+=this->dt*this->vy2;   this->z2+=this->dt*this->vz2;
        //cout << "position 1: (" << this->x1 << "," << this->y1 << "," << this->z1 << ")" << endl;
        //cout << "position 2: (" << this->x2 << "," << this->y2 << "," << this->z2 << ")" << endl;

        //update speed
        this->vx1+=this->dt*F21x/this->m1;  this->vy1+=this->dt*F21y/this->m1;  this->vz1+=this->dt*F21z/this->m1;
        this->vx2-=this->dt*F21x/this->m2;  this->vy2-=this->dt*F21y/this->m2;  this->vz2-=this->dt*F21z/this->m2;
        //cout << "speed 1: (" << this->vx1 << "," << this->vy1 << "," << this->vz1 << ")" << endl;
        //cout << "speed 2: (" << this->vx2 << "," << this->vy2 << "," << this->vz2 << ")" << endl;

        //update the objects position
        this->SphereSource->SetCenter(this->x1,this->y1,this->z1);
        this->SphereSource->Update();
        this->SphereSource2->SetCenter(this->x2,this->y2,this->z2);
        this->SphereSource2->Update();

        //even though it is a shallow copy, it must be computed otherwise the data are lost... meh!
        input1->ShallowCopy(this->SphereSource->GetOutput());
        input2->ShallowCopy(this->SphereSource2->GetOutput());
        appendFilter->Update();

        // Remove any duplicate points.
        this->cleanFilter->SetInputConnection(appendFilter->GetOutputPort());
        this->cleanFilter->Update();

        //actualy render the output scene in the window
        ren->Render();

    }

    void EndCue(vtkAnimationCue::AnimationCueInfo *vtkNotUsed(info), vtkRenderer *ren)
    {
        (void)ren;
        // don't remove the actor for the regression image.
        //      ren->RemoveActor(this->Actor);
        this->Cleanup();
    }
 
protected:
    //time between frame
    double dt, alpha, m1, m2;

    //one object and its position and speed
    vtkSphereSource *SphereSource;
    double x1, y1, z1;
    double vx1, vy1, vz1;

    //another object and its position and speed
    vtkSphereSource *SphereSource2;
    double x2, y2, z2;
    double vx2, vy2, vz2;

    //temporary container for the spheres
    vtkPolyData* input1;
    vtkPolyData* input2;

    //global container for the two spheres and a clean version with no repetitions
    vtkAppendPolyData* appendFilter;
    vtkCleanPolyData* cleanFilter;

    //object for plotting
    vtkPolyDataMapper *Mapper;
    vtkActor *Actor;

    void Cleanup()
    {
        if(this->SphereSource!=0)
        {
            this->SphereSource->Delete();
            this->SphereSource=0;
        }

        if(this->SphereSource2!=0)
        {
            this->SphereSource2->Delete();
            this->SphereSource2=0;
        }

        if(this->input1!=0)
        {
            this->input1->Delete();
            this->input1=0;
        }

        if(this->input2!=0)
        {
            this->input2->Delete();
            this->input2=0;
        }
        if(this->appendFilter==0)
        {
            this->appendFilter->Delete();
            this->appendFilter=0;
        }
        if(this->cleanFilter==0)
        {
            this->cleanFilter->Delete();
            this->cleanFilter=0;
        }

        if(this->Mapper!=0)
        {
            this->Mapper->Delete();
            this->Mapper=0;
        }

        if(this->Actor!=0)
        {
            this->Actor->Delete();
            this->Actor=0;
        }

    }
};
 
class vtkAnimationCueObserver : public vtkCommand
{
public:
    //ctor
    static vtkAnimationCueObserver *New()
    {
        return new vtkAnimationCueObserver;
    }

    //function for the window thread (what to do for each events). It is implicitely call by the call back function
    virtual void Execute(vtkObject *vtkNotUsed(caller), unsigned long event, void *calldata)
    {
        if(this->Animator!=0 && this->Renderer!=0)
        {
            vtkAnimationCue::AnimationCueInfo *info= static_cast<vtkAnimationCue::AnimationCueInfo *>(calldata);
            switch(event)
            {
                //what to do at the beginning of the scene
                case vtkCommand::StartAnimationCueEvent:
                    this->Animator->initScene(info,this->Renderer);
                    break;
                //what to do at the end of the scene
                case vtkCommand::EndAnimationCueEvent:
                    this->Animator->EndCue(info,this->Renderer);
                    break;
                //how to update the scene
                case vtkCommand::AnimationCueTickEvent:
                    this->Animator->updateObjectsPosition(info,this->Renderer);
                    break;
            }
        }
        if(this->RenWin!=0)
        {
            this->RenWin->Render();
        }
    }

    //attributes for the annimation
    vtkRenderer *Renderer;
    vtkRenderWindow *RenWin;
    sceneCalculator *Animator; //the actual calculator of the scene

protected:
    vtkAnimationCueObserver()
    {
        this->Renderer=0;
        this->Animator=0;
        this->RenWin=0;
    }
};
 
int main(int, char *[])
{
    // Create the graphics structure. The renderer renders into the
    // render window.
    vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
    renWin->SetMultiSamples(0);
    iren->SetRenderWindow(renWin);
    renWin->AddRenderer(ren1);
    renWin->Render();

    // Create an Animation Scene
    vtkSmartPointer<vtkAnimationScene> scene = vtkSmartPointer<vtkAnimationScene>::New();

    scene->SetModeToRealTime(); //play the scene using the actual time
    //scene->SetModeToSequence(); //play the scene using default time between frame and starts imediately

    scene->SetLoop(0); //0: no loop animation; not 0: while true...
    scene->SetFrameRate(2); //? no effect?
    scene->SetStartTime(0); //starting time
    scene->SetEndTime(10); //end of the annimation

    // Create an Animation Cue.
    vtkSmartPointer<vtkAnimationCue> cue1 = vtkSmartPointer<vtkAnimationCue>::New();
    cue1->SetStartTime(0); //when the calculation starts
    cue1->SetEndTime(10); //when it ends
    scene->AddCue(cue1);  //what it does

    // Create an object that can simulate a scene
    sceneCalculator animator;

    // Create Cue observer.
    vtkSmartPointer<vtkAnimationCueObserver> observer = vtkSmartPointer<vtkAnimationCueObserver>::New();
    observer->Renderer=ren1;
    observer->Animator=&animator;
    observer->RenWin=renWin;

    //set the actions init, end and iteration
    cue1->AddObserver(vtkCommand::StartAnimationCueEvent,observer);
    cue1->AddObserver(vtkCommand::EndAnimationCueEvent,observer);
    cue1->AddObserver(vtkCommand::AnimationCueTickEvent,observer);

    //start the scene
    scene->Play();
    scene->Stop(); //no real effect because the scene stops at some point

    //just so that at the end, you can play with the scene
    iren->Start();

    return EXIT_SUCCESS;
}
