#pragma once

#include "ofMain.h"
#include "ofxShadertoy.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
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
		
        ofxShadertoy shadertoy;
    
    ofxPanel gui_main;
    ofParameter<bool> bShowGui;
    ofParameter<bool> bShowGrid;
       ofParameter<float> val_x;
    ofParameter<float> val_y;
    ofParameter<float> val_z;
      ofParameter<float> val_w;
                          
    ofParameter<float>  offset_x;
    ofParameter<float>  offset_y;
    
     ofTexture tex;
 };
