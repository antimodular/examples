#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void exit();

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

//    ofxPanel gui_switchGui;
//    string switchNameStr[2];
//    ofParameter<string> switchNamePar[2];
//    ofParameter<bool> useSwitchTime[2];
//    ofParameter<int> switchTimeHour[2];
//    ofParameter<int> switchTimeMinute[2];
//    int switchTimeAllInMinutes[2];
//    int currentSwitchGui;
    
    ofParameter<bool> bShowGui;
    
    ofxPanel gui_switchGui;
    string switchNameStr[2];
    ofParameter<string> switchNamePar[2];
    ofParameter<bool> useSwitchTime[2];
    ofParameter<int> switchTimeHour[2];
    ofParameter<int> switchTimeMinute[2];
    int switchTimeAllInMinutes[2];
    int currentSwitchGui;
    
      ofxPanel gui_color;
    ofParameter<ofColor> myColor;
    ofParameter<int> xmlFileVersion;
    int old_xmlFileVersion;
};

