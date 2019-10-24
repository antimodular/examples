#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    sftp_object.setup();
    
    optionCnt = 0;
    
    for(int i=0; i<6;i++){
        options.push_back(i+1);
    }
    
    sendString = "0";
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetWindowTitle("fps "+ofToString(ofGetFrameRate(),2));
    if(ofGetElapsedTimef()-uploadTimer > 5){
        uploadTimer = ofGetElapsedTimef();
        
        sendString = "";
        
        
        //0 = none
        //1 = all
        //
        
        
        options.clear();
        for(int i=0; i<6;i++){
            options.push_back(i+1);
        }
        
        //pair 1
        int rr = ofRandom(options.size());
        sendString += ofToString( options[rr]);
        options.erase(options.begin()+rr);
        rr = ofRandom(options.size());
        sendString += ofToString( options[rr]);
        options.erase(options.begin()+rr);
        
        //pair 2
        rr = ofRandom(options.size());
        sendString += ofToString( options[rr]);
        options.erase(options.begin()+rr);
        rr = ofRandom(options.size());
        sendString += ofToString( options[rr]);
        options.erase(options.begin()+rr);
        
        //pair 3
        rr = ofRandom(options.size());
        sendString += ofToString( options[rr]);
        options.erase(options.begin()+rr);
        rr = ofRandom(options.size());
        sendString += ofToString( options[rr]);
        
        ofLog()<<"sendString "<<sendString;
        sftp_object.addSFTP(sendString);
    }
    
    sftp_object.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    sftp_object.draw(10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
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
