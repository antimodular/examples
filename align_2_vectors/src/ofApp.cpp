#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    ofSetWindowPosition(600,100);
    
    objectMesh.addVertex(ofVec3f(100,100,0));
    objectMesh.addVertex(ofVec3f(200,50,0));
 
    enterPoint = ofVec3f(ofRandom(50,300),ofRandom(50,300),0);
    exitPoint = ofVec3f(ofRandom(50,300),ofRandom(50,300),0);
}

//--------------------------------------------------------------
void ofApp::update(){



}

void ofApp::draw(){
    
    //--draw via matrix multiplication
    ofSetColor(255);
    ofDrawBitmapString("matrix multiplication",10,10);

    
    ofNoFill();
    ofSetColor(0);
     ofSetLineWidth(1);
    ofDrawRectangle(0,0,300,300);
    
    ofPoint child1 = objectMesh.getVertex(0);
    ofPoint child2 = objectMesh.getVertex(1);
    ofMatrix4x4 mat = aling_twoVectors(enterPoint,exitPoint,child1,child2);
    
    //mother vector
    ofSetColor(255,0,0);
    ofSetLineWidth(5);
    ofDrawLine(enterPoint,exitPoint);
    ofDrawSphere(enterPoint,5);
    ofSetLineWidth(1);

    ofSetColor(255);
    ofDrawBitmapString("mother",enterPoint.getMiddle(exitPoint));

    
    //--draw via push/pop, adjusted child vector
    child1 = child1 * mat;
    child2 = child2 * mat;
    
    ofSetColor(100,0,100);
    ofSetLineWidth(3);
    ofDrawLine(child1,child2);
    
    ofSetColor(255);
    ofDrawBitmapString("child",child1.getMiddle(child2));

    ofPushMatrix();
    ofTranslate(300, 0);
    ofSetColor(255);
    ofDrawBitmapString("push / pop",10,10);

    ofNoFill();
    ofSetColor(0);
    ofSetLineWidth(1);
    ofDrawRectangle(0,0,300,300);
    align();
    ofPopMatrix();
    //offset_align();
}

ofMatrix4x4 ofApp::aling_twoVectors(ofVec3f mother1,ofVec3f mother2, ofVec3f child1, ofVec3f child2){
    
    //path through sphere
    ofVec3f v1 = mother2 - mother1; // exitPoint - enterPoint
    v1.normalize();
    
    // 3d model    
    ofVec3f v2 = child2 - child1;
    v2.normalize();
    
    ofVec3f cross = v2.getCrossed(v1);
    float   angle = v2.angle(v1);
    
    ofMatrix4x4 trans_to0;
    trans_to0.makeTranslationMatrix(mother1);
    
    ofMatrix4x4 rot_toAlign;
    rot_toAlign.makeRotationMatrix(angle-180, cross.x,cross.y,cross.z);
    
    ofMatrix4x4 trans_toEnter;
    trans_toEnter.makeTranslationMatrix(-child1);
    
    ofMatrix4x4 main_mat;
    main_mat = trans_toEnter * rot_toAlign * trans_to0;
    
    return main_mat;
}

void ofApp::align(){

    ofSetColor(255,0,0);
    ofSetLineWidth(5);
    ofDrawLine(enterPoint,exitPoint);
    ofDrawSphere(enterPoint,5);
    ofSetLineWidth(1);

    
    ofVec3f v1 = exitPoint - enterPoint;
    v1.normalize();

    ofVec3f p1 = objectMesh.getVertex(0);
    ofVec3f p2 = objectMesh.getVertex(1);
    
    ofVec3f v2 = p2 - p1;
    v2.normalize();
    
    ofVec3f cross = v2.getCrossed(v1);
    float   angle = v2.angle(v1);    
    
    ofPushMatrix();
    
    ofTranslate(enterPoint);
    ofRotateDeg(angle-180, cross.x,cross.y,cross.z);
    ofTranslate(-p1);
    
    ofSetColor(255);
    ofSetLineWidth(1);
    ofDrawLine(p1,p2);
    ofPopMatrix();

    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    enterPoint = ofVec3f(ofRandom(50,150),ofRandom(50,150),0);
    exitPoint = ofVec3f(ofRandom(50,290),ofRandom(50,290),0);

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
