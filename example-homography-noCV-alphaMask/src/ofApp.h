#pragma once

#include "ofMain.h"
#include "ofxHomography.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	bool movePoint(vector<ofVec2f>& points, ofVec2f point);
	void mousePressed(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void keyPressed(int key);
	void resetPoints();
	void loadPoints();
	
	ofImage left, right, warpedColor;
	vector<ofVec2f> leftPoints, rightPoints;
	bool movingPoint;
	ofVec2f* curPoint;
	bool saveMatrix;
	bool homographyReady;
	
	glm::mat4 homography;
	
	// Mask and FBO related
	ofFbo maskFbo;
	ofFbo warpFbo;  // New FBO for warped image
	float maskRadius;
	ofVec2f maskCenter;
	bool maskEnabled;
};
