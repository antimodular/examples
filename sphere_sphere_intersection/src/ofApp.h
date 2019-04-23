#pragma once

#include "ofMain.h"

#include "ofxGui.h"

#include "customDefines.h"

#include "ofxCameraSaveLoad.h"

#include "oneTestPoint.h"

class ofApp : public ofBaseApp{
    
public:
    
    string versionString;
    ofxLabel versionLabel;
    
    void setup();
    void exit();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    //--gui
    void checkGui();
    void saveGui();
    
    ofxPanel gui_main;
    ofParameter<bool> bShowGui;

    
    //---3D Camera
    ofxPanel gui_easyCam;
    ofParameter<bool> bEnableCamMouse;
    ofParameter<bool> bLoadCamPos, bSaveCamPos;
    ofParameter<bool> bShowMainCam;
    ofParameter<bool> bShowSideCams;
    
    ofLight roomLight;

    ofPlanePrimitive floor;
//    ofMaterial roadMaterial;
    
    void draw3d();
    void drawScene(int iCameraDraw);
    ofEasyCam easyCam;
    
    ofCamera camFront;
    ofCamera camTop;
    ofCamera camLeft;

      ofVec3f mouseP_3d;
    //camera pointers
    ofCamera * cameras[N_CAMERAS];
    int iMainCamera;

    
    //---view ports
    //viewports
    ofRectangle viewMain;
    ofRectangle viewGrid[N_CAMERAS];
    
    //----point picker
    float nearestDistance = 0;
    ofVec2f nearest3DPoint, nearest2DPoint;
    int nearestIndex = 0;
    
   
    //------collected data
    
    vector<ofPoint> tripod_positions;
    vector<ofPoint> reference_positions;
    
    vector<oneTestPoint> allTestPoints;
    
    vector<float> reference_distances;
    
//    //------intersection
//      ofxIntersection is;
//    IsRay ray;
//    IsPlane planes[NUM_PLANES];
//    ofMesh mesh;
//    ofMesh planecut;
    
    int testPoint_index;
    
    bool bShowSphere;
};
