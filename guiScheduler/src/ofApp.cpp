#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    bShowGui = true;
    
    //------gui scheduler
    gui_color.setup();
    gui_color.setName("color");
    gui_color.setPosition(10,200);
    gui_color.setHeaderBackgroundColor(ofColor(255,0,0));
    gui_color.add(xmlFileVersion.set("xml file",0,0,1));
    gui_color.add(myColor.set("BG color", ofColor(255,0,0),ofColor(0,0,0),ofColor(255,255,255)));
    
    
    //------gui scheduler
    gui_switchGui.setup();
    gui_switchGui.setName("switchTimes");
    gui_switchGui.setPosition(10,10);
    gui_switchGui.setHeaderBackgroundColor(ofColor(255,0,0));
    
    switchNameStr[0] = "ON time";
    switchNameStr[1] = "OFF time";
    
    for(int i=0; i<2;i++){
        gui_switchGui.add(switchNamePar[i].set(switchNameStr[i],""));
        gui_switchGui.add(useSwitchTime[i].set("useTime_"+ofToString(i),false));
        gui_switchGui.add(switchTimeHour[i].set("hour_"+ofToString(i),0,0,23));
        gui_switchGui.add(switchTimeMinute[i].set("minute_"+ofToString(i),0,0,59));
    }
    gui_switchGui.loadFromFile("GUIs/gui_switchGui.xml");
    //    gui_switchGui.minimizeAll();
    
    
    ofLog()<<"current time H:M "<<ofGetHours()<<" : "<<ofGetMinutes();
    int current_timeInMin = ofGetHours()*60 + ofGetMinutes();
    ofLog()<<"current time ALL min "<<current_timeInMin;
    
    
    currentSwitchGui = -1;
    
    //now lets see if we past a scheduled time
    
    switchTimeAllInMinutes[0] = switchTimeHour[0] * 60 + switchTimeMinute[0];
    switchTimeAllInMinutes[1] = switchTimeHour[1] * 60 + switchTimeMinute[1];
    
    if(useSwitchTime[0] == true){
        if(current_timeInMin >= switchTimeAllInMinutes[0]){
            ofLog()<<"it's ON time. switchTimeAllInMinutes[0] "<<switchTimeAllInMinutes[0];
            currentSwitchGui = 0;
        }else{
            ofLog()<<"it's NOT ON time";   
        }
        
    }
    
    if(useSwitchTime[1] == true){
        if(current_timeInMin >= switchTimeAllInMinutes[1]){
            ofLog()<<"it's OFF time. switchTimeAllInMinutes[1] "<<switchTimeAllInMinutes[1];
            
            currentSwitchGui = 1;
        }else{
            ofLog()<<"it's NOT OFF time";   
        }
        
    }
    
    gui_color.loadFromFile("GUIs/gui_color_"+ofToString(xmlFileVersion)+".xml");
    gui_color.maximizeAll();
    
}


//--------------------------------------------------------------
void ofApp::exit(){
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for(int i=0; i<2; i++){
        if(useSwitchTime[i] == true && i != currentSwitchGui){
            //            if((ofGetHours() - switchTimeHour[i] == 0 && ofGetMinutes() - switchTimeMinute[i] >= 0) || ofGetHours() - switchTimeHour[i] > 0){
            if(ofGetHours() - switchTimeHour[i] == 0 && ofGetMinutes() - switchTimeMinute[i] == 0){
                
                ofLog()<<i<<" update() gui time is "<<switchTimeHour[i]<<" : "<<switchTimeMinute[i]<<" switchNameStr[i]  "<<switchNameStr[i] ;
                
                if(i == 0){
                    currentSwitchGui = i;
                } else if(i == 1){
                    
                    currentSwitchGui = i;
                }
                
                gui_color.loadFromFile("GUIs/gui_color_"+ofToString(currentSwitchGui)+".xml");
               xmlFileVersion = currentSwitchGui;
                old_xmlFileVersion = xmlFileVersion;
                ofLog()<<"timer loaded gui_color "<<("GUIs/gui_color_"+ofToString(currentSwitchGui)+".xml");

                
            }
        }
    }
    
    if(old_xmlFileVersion != xmlFileVersion){
        old_xmlFileVersion = xmlFileVersion;
        gui_color.loadFromFile("GUIs/gui_color_"+ofToString(xmlFileVersion)+".xml");
        ofLog()<<"gui change loaded gui_color "<<("GUIs/gui_color_"+ofToString(xmlFileVersion)+".xml");
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetBackgroundColor(myColor);
    int tempY = 10;
    
    ofDrawBitmapString("current time H:M "+ofToString(ofGetHours())+" : "+ofToString(ofGetMinutes()), 300, tempY+=15);
    
    ofDrawBitmapString("currentSwitchGui == "+switchNameStr[currentSwitchGui], 300, tempY+=15);
    //     ofDrawBitmapString("cur mintues: "+ofToString(current_timeInMin), 300, tempY+=15);
    //    ofDrawBitmapString("it's on time: "+ofToString(itsONtime) + " : " +ofToString(switchTimeAllInMinutes[0]), 300, tempY+=15);
    //    ofDrawBitmapString("it's off time: "+ofToString(itsOFFtime) + " : " +ofToString(switchTimeAllInMinutes[1]), 300, tempY+=15);
    
    if(bShowGui == true){
        gui_switchGui.draw();
        gui_color.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'g'){
        bShowGui = !bShowGui;
        if(bShowGui == false){
            gui_switchGui.saveToFile("GUIs/gui_switchGui.xml");
            gui_color.saveToFile("GUIs/gui_color_"+ofToString(xmlFileVersion)+".xml");
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
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
