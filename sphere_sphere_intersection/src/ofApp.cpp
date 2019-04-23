#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(200);
    ofSetFrameRate(30);
    
    
    //    ofEnableDepthTest();
    
    roomLight.setup();
    roomLight.setPosition(-100, 1000,0);
    // we set up a floor on which the car will move
    floor.set(10000, 10000);

    //------3d camera
    
    iMainCamera = 0;
    

    
    easyCam.setFarClip(10000);
    easyCam.setupPerspective();
    easyCam.setVFlip(false);
    easyCam.setDistance(3000);
    cameras[0] = &easyCam;
    
    // front
    ofxLoadCamera(camFront, "sceneFront");
    cameras[1] = &camFront;
    
    // top
    ofxLoadCamera(camTop, "sceneTop");
    cameras[2] = &camTop;
    
    // left
    ofxLoadCamera(camLeft, "sceneLeft");
    cameras[3] = &camLeft;
    
    float xOffset = DISPLAY_WIDTH / 3;
    float yOffset = DISPLAY_HEIGHT / N_CAMERAS;
    
    
    viewMain.x = DISPLAY_WIDTH - (xOffset*2);
    viewMain.y = 0;
    viewMain.width = xOffset * 2;
    viewMain.height = DISPLAY_HEIGHT;
    
    //    viewMain = ofRectangle(0,0,ofGetWidth(),ofGetHeight());
    
    for(int i = 0; i < N_CAMERAS; i++){
        
        viewGrid[i].x = DISPLAY_WIDTH - (xOffset*3);
        viewGrid[i].y = yOffset * i;
        viewGrid[i].width = xOffset;
        viewGrid[i].height = yOffset;
    }
    ofSetSphereResolution(200);
    ofSetCircleResolution(200);
    //-----------GUI --------
    int gui_x = 10;
    int gui_y = 10;
    int gui_w = 210;
    int gui_h = 350;
    
    gui_main.setup();
    gui_main.setName("sphereSphere");
    gui_main.setPosition(gui_x,gui_y);
    gui_main.add(bShowGui.set("showGui",false));
    
    gui_main.loadFromFile("gui_main.xml");
    

    gui_easyCam.setup();
    gui_easyCam.setName("scene_camera");
    gui_easyCam.setPosition(gui_x+=gui_w,gui_y);
    
    gui_easyCam.add(bShowMainCam.set("showMainCam", true));
    gui_easyCam.add(bShowSideCams.set("showSideCams", false));
    gui_easyCam.add(bEnableCamMouse.set("moveByMouse", false));
    gui_easyCam.add(bLoadCamPos.set("bLoadCamPos", false));
    gui_easyCam.add(bSaveCamPos.set("bSaveCamPos", false));
    gui_easyCam.loadFromFile("gui_easyCam.xml");
    
    
    
    bLoadCamPos = true;
    
    testPoint_index = 4;
    
    tripod_positions.resize(3);
    
    tripod_positions[0] = ofPoint(0.000, 0.000, 0.000); //T0
    tripod_positions[1] = ofPoint(259.0, 0.000, 0.000); //T1
    tripod_positions[2] = ofPoint(137.6, 228.7, 0.000); //T2
    
    //    reference_positions.push_back(ofPoint());
    
    oneTestPoint temp_p;
    //point a
    temp_p.distances.push_back(155); 
    temp_p.distances.push_back(414);
    temp_p.distances.push_back(366);
    allTestPoints.push_back(temp_p);
    allTestPoints.back().getIntersections(tripod_positions);
    allTestPoints.back().label = "a";
    
    //point b
    temp_p.distances.clear();
    temp_p.distances.push_back(345); 
    temp_p.distances.push_back(468);
    temp_p.distances.push_back(230);
    allTestPoints.push_back(temp_p);
    allTestPoints.back().getIntersections(tripod_positions);
    allTestPoints.back().label = "b";
    
    //point c
    temp_p.distances.clear();
    temp_p.distances.push_back(573); 
    temp_p.distances.push_back(503);
    temp_p.distances.push_back(306);
    allTestPoints.push_back(temp_p);
    allTestPoints.back().getIntersections(tripod_positions);
    allTestPoints.back().label = "c";
    
    //point d
    temp_p.distances.clear();
    temp_p.distances.push_back(478); 
    temp_p.distances.push_back(310);
    temp_p.distances.push_back(253);
    allTestPoints.push_back(temp_p);
    allTestPoints.back().getIntersections(tripod_positions);
    allTestPoints.back().label = "d";
    
    //off zero plane
    //point e 
    temp_p.distances.clear();
    temp_p.distances.push_back(502); 
    temp_p.distances.push_back(348);
    temp_p.distances.push_back(298);
    allTestPoints.push_back(temp_p);
    allTestPoints.back().getIntersections(tripod_positions);
    allTestPoints.back().label = "e";
    
    //point f
    temp_p.distances.clear();
    temp_p.distances.push_back(478); 
    temp_p.distances.push_back(310);
    temp_p.distances.push_back(253);
    allTestPoints.push_back(temp_p);
    allTestPoints.back().getIntersections(tripod_positions);
    allTestPoints.back().label = "f";
    
    //point g
    temp_p.distances.clear();
    temp_p.distances.push_back(211); 
    temp_p.distances.push_back(438);
    temp_p.distances.push_back(394);
    allTestPoints.push_back(temp_p);
    allTestPoints.back().getIntersections(tripod_positions);
    allTestPoints.back().label = "g";
    
    //point x
    temp_p.distances.clear();
    temp_p.distances.push_back(150); 
    temp_p.distances.push_back(150);
    temp_p.distances.push_back(150);
    allTestPoints.push_back(temp_p);
    allTestPoints.back().getIntersections(tripod_positions);
    allTestPoints.back().label = "x";
    
    vector<ofColor> temp_colors;
    temp_colors.push_back(ofColor(245,217,84));
    temp_colors.push_back(ofColor(229,98,69));
    temp_colors.push_back(ofColor(112,189,248));
    for(auto& p: allTestPoints){
        p.tripod_colors.push_back(temp_colors[0]);
        p.tripod_colors.push_back(temp_colors[1]);
        p.tripod_colors.push_back(temp_colors[2]);
        
        p.setup();
    }
    ofLog()<<"----setup done----";
}


void ofApp::exit(){
    //all off
    
}
//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetWindowTitle(ofToString(ofGetFrameRate(),1));

    checkGui();
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    draw3d();
    allTestPoints[testPoint_index].drawInfo();
    
    ofDrawBitmapStringHighlight("key s = toggle spheres", 400,50);
    ofDrawBitmapStringHighlight("arrow keys = different values", 400,70);
    
    if(bShowGui){
        gui_main.draw();
        gui_easyCam.draw();
    }
}

void ofApp::draw3d(){
    
    ofEnableDepthTest();
    // draw side viewports
    
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    //    ofPushMatrix();
    //    ofRotate();
    ofVec3f mouseP(300, 300 ,ofGetMouseY());
    mouseP_3d = cameras[0]->screenToWorld(mouseP, viewMain);
    
    if(bShowSideCams == true){
        for(int i = 0; i < N_CAMERAS; i++){
            cameras[i]->begin(viewGrid[i]);
            drawScene(i);
            cameras[i]->end();
        }
    }
    
    // draw main viewport
    if(bShowMainCam == true){
        cameras[iMainCamera]->begin(viewMain);
        drawScene(iMainCamera);
        cameras[iMainCamera]->end();
    }
    
    
    // draw on top of everything
    ofPushStyle();
    glDepthFunc(GL_ALWAYS); 
    
    
    // draw outlines on viewports
    ofSetLineWidth(2);
    ofNoFill();
    ofSetColor(255, 255, 255);
    if(bShowSideCams == true){
        //
        for(int i = 0; i < N_CAMERAS; i++){
            ofDrawRectangle(viewGrid[i]);
        }
    }
    //
    if(bShowMainCam == true) ofDrawRectangle(viewMain);
    
    // restore the GL depth function
    glDepthFunc(GL_LESS);
    ofPopStyle();
    
    
    ofDisableDepthTest();
    
    
}

void ofApp::drawScene(int iCameraDraw){
    
    
    ofSetColor(50); ;

    //draw an axis at each tripod location
    for(auto& onetripod: tripod_positions){
        ofPushMatrix();
        ofTranslate(onetripod);
        ofDrawAxis(40);
        ofPopMatrix();
    }
    
    
    
    allTestPoints[testPoint_index].draw(tripod_positions,bShowSphere);
    
}

void ofApp::saveGui(){
    
    ofLogNotice("ofApp")<<"saveGui"<<endl;
    gui_main.saveToFile("gui_main.xml");
    gui_easyCam.saveToFile("gui_easyCam.xml");
    
    
}

void ofApp::checkGui(){
    
    
    if(bSaveCamPos){
        bSaveCamPos = false;
        ofLog()<<"save sceneCamera";
        ofxSaveCamera(easyCam, "sceneCamera");
    }
    if(bLoadCamPos){
        bLoadCamPos = false;
        ofLog()<<"load sceneCamera";
        ofxLoadCamera(easyCam, "sceneCamera");
    }
    
    //3d viewing paramters
    if(bEnableCamMouse){
        easyCam.enableMouseInput();
        easyCam.enableMouseMiddleButton();
    }else{
        easyCam.disableMouseInput();
        easyCam.disableMouseMiddleButton();
    }
    
    
    
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    
    if(key == 'g'){
        bShowGui = !bShowGui;
        ofLog()<<"bShowGui "<<bShowGui;
        if(bShowGui == false){
            saveGui();
            //            ofHideCursor();
        }else{
            //            ofShowCursor();
        }
    }
    
    if(key == 'f') ofToggleFullscreen();
    
    if(key == OF_KEY_LEFT){
        testPoint_index--;
    }
    if(key == OF_KEY_RIGHT){
        testPoint_index++;
    }
    
    testPoint_index %= allTestPoints.size();
    
    if(key =='s'){
        bShowSphere = !bShowSphere;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}


