#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //-----------GUI --------
    int gui_x = 10;
    int gui_y = 10;
    int gui_w = 210;
    int gui_h = 350;
    
    gui_main.setup();
    gui_main.setName("polarGrid");
    gui_main.setPosition(gui_x,gui_y);
    
    gui_main.add(bShowGui.set("bShowGui",true));
    
     gui_main.add(bShowGrid.set("bShowGrid",false));
    //vec4(2.0 + cos(iTime), 5.0, M_PI/6., 5.*M_PI/6.+ 4.*sin(iTime/2.)*M_PI/6.);
    gui_main.add(val_x.set("X",0,0,PI));
    gui_main.add(val_y.set("Y",M_PI,0,2*M_PI));
    gui_main.add(val_z.set("Z",0,0,2*M_PI));
    gui_main.add(val_w.set("W",M_PI,0,2*M_PI));
    
    gui_main.add(offset_x.set("offset_x",0,-1,1));
    gui_main.add(offset_y.set("offset_y",0,-1,1));
    gui_main.loadFromFile("gui_main.xml");
    
    shadertoy.load("shaders/polarGrid.frag");
    ofImage img;
    img.load("img.jpg");
    img.resize(1024,1024);
    ofLog()<<"img "<<img.getWidth()<<" , "<< img.getHeight();
   
    tex.allocate(img.getWidth(), img.getHeight(), GL_RGBA, false); // fourth parameter is false to avoid generation of a GL_TEXTURE_2D_RECTANGLE texture - we don't want this.
    tex.loadData(img.getPixels());
    //    tex.generateMipmap();
    //    tex.setTextureWrap(GL_REPEAT, GL_REPEAT);
    shadertoy.setTexture(0, tex);
    ofSetFrameRate(60);
    //    shadertoy.setAdvanceTime(true);
    //    shadertoy.setUseMouse(true);
    
      ofSetCircleResolution(100);
}

//--------------------------------------------------------------
void ofApp::update(){
    shadertoy.setCustomVec3(ofVec3f(offset_x,offset_y,0));
    shadertoy.setCustomVec4(val_x,val_y,val_z,val_w);
    shadertoy.setCustomInt0(int(bShowGrid));
}

//--------------------------------------------------------------
void ofApp::draw(){
    
       
    ofFill();
    shadertoy.draw(0, 0,1024,768); //, ofGetWindowWidth(), ofGetWindowHeight());
    
    ofSetColor(255);
    tex.draw(1,1,tex.getWidth()/4,tex.getHeight()/4);

    
    if(bShowGui) {
        gui_main.draw();
    }
    
    ofNoFill();
    ofSetColor(255);
    ofDrawCircle(mouseX,mouseY, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'f') {
        ofToggleFullscreen();
    }
    
    if(key == 'g'){
        bShowGui = !bShowGui;
        if(bShowGui == false) gui_main.saveToFile("gui_main.xml"); 
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
