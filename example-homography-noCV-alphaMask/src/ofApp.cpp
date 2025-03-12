#include "ofApp.h"


void ofApp::setup() {
	ofSetVerticalSync(true);
	
	left.load("left.jpg");
	right.load("right.jpg");
    // right.resize(right.getWidth()*0.6,right.getHeight()*0.6);
    
	// Setup FBOs
	warpFbo.allocate(left.getWidth(), left.getHeight(), GL_RGBA);
	maskFbo.allocate(left.getWidth(), left.getHeight(), GL_RGBA);
	
	// Initialize mask parameters
	maskRadius = 200;
	maskCenter.set(left.getWidth()/2, left.getHeight()/2);
	maskEnabled = true;
	
	// Clear FBOs
	warpFbo.begin();
	ofClear(0, 0, 0, 0);
	warpFbo.end();
	
	maskFbo.begin();
	ofClear(0, 0, 0, 0);
	maskFbo.end();
	
	movingPoint = false;
	saveMatrix = false;
	homographyReady = false;
	
	ofLogNotice() << "Left image size: " << left.getWidth() << "x" << left.getHeight();
	ofLogNotice() << "Right image size: " << right.getWidth() << "x" << right.getHeight();
	ofLogNotice() << "Warped image size: " << warpedColor.getWidth() << "x" << warpedColor.getHeight();
	
	
}

void ofApp::update() {

	
	if(leftPoints.size() >= 4) {
		vector<glm::vec3> srcPoints, dstPoints;
		
		// Convert points to glm::vec3, adjusting right points to be relative to their image
		for(int i = 0; i < 4; i++) {
			srcPoints.push_back(glm::vec3(rightPoints[i].x - left.getWidth(), rightPoints[i].y, 0));
			dstPoints.push_back(glm::vec3(leftPoints[i].x, leftPoints[i].y, 0));
			
			// Debug point coordinates
			ofLogNotice() << "Point " << i << " src: " << srcPoints[i].x << "," << srcPoints[i].y 
						 << " dst: " << dstPoints[i].x << "," << dstPoints[i].y;
		}
		
		// Generate homography using ofxHomography
		homography = ofxHomography::findHomography(srcPoints, dstPoints);
		homographyReady = true;
		
		// Debug: Print homography matrix
		ofLogNotice() << "Homography Matrix:";
		for(int i = 0; i < 4; i++) {
			ofLogNotice() << homography[i][0] << " " << homography[i][1] << " "
						 << homography[i][2] << " " << homography[i][3];
		}
		
		if(saveMatrix) {
			ofFile file("homography.txt", ofFile::WriteOnly);
			const float* values = glm::value_ptr(homography);
			for(int i = 0; i < 16; i++) {
				file << ofToString(values[i]) << "\n";
			}
			file.close();
			saveMatrix = false;
		}
	}
}

void drawPoints(vector<ofVec2f>& points) {
	ofNoFill();
	for(int i = 0; i < points.size(); i++) {
		ofDrawCircle(points[i], 10);
		ofDrawCircle(points[i], 1);
	}
}

void ofApp::draw() {
	ofBackground(0); // Black background
	
	// Draw original images
	ofSetColor(255);
	left.draw(0, 0);
	right.draw(left.getWidth(), 0);
	
	// Draw warped image with mask
	if(homographyReady) {
		// First render warped image to FBO
		ofPushStyle();
		warpFbo.begin();
			ofClear(0, 0, 0, 0);
			ofPushMatrix();
			ofMultMatrix(homography);
			ofSetColor(255);
			right.draw(0, 0);
			ofPopMatrix();
		warpFbo.end();
		ofPopStyle();
		
		// Update mask FBO
		ofPushStyle();
		maskFbo.begin();
			ofClear(0, 0, 0, 0);
			ofSetColor(255);
			ofFill();
//			ofPushMatrix();
			// ofMultMatrix(homography);
			ofDrawCircle(maskCenter.x, maskCenter.y, maskRadius);
//			ofPopMatrix();
		maskFbo.end();
		ofPopStyle();
		
		// Apply mask and draw
		if(maskEnabled) {
			warpFbo.getTexture().setAlphaMask(maskFbo.getTexture());
		} else {
			warpFbo.getTexture().disableAlphaMask();
		}
		
		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255, 128); // 50% opacity
		warpFbo.draw(0, 0);
        
        ofSetColor(ofColor::yellow); // to show
        ofNoFill();
        ofDrawCircle(maskCenter.x, maskCenter.y, maskRadius);
		ofDisableAlphaBlending();
		
	}
	
	// Draw control points
	ofSetColor(ofColor::red);
	drawPoints(leftPoints);
	ofSetColor(ofColor::blue);
	drawPoints(rightPoints);
	
	// Draw lines between corresponding points
	ofSetColor(128);
	for(int i = 0; i < leftPoints.size(); i++) {
		ofDrawLine(leftPoints[i], rightPoints[i]);
	}
	
	// Draw debug information
	ofSetColor(255);
	string debugInfo = "FPS: " + ofToString((int)ofGetFrameRate()) + "\n";
	debugInfo += "Points: " + ofToString(leftPoints.size()) + "/4\n";
	debugInfo += "Homography Ready: " + string(homographyReady ? "YES" : "NO") + "\n";
	debugInfo += "Mask: " + string(maskEnabled ? "ON" : "OFF") + "\n";
	if(homographyReady) {
		debugInfo += "Press SPACE to save matrix\n";
	}
	debugInfo += "Press 'm' to toggle mask\n";
	debugInfo += "Press 'r' to reset points\n";
	debugInfo += "Press 'l' to load points\n";
	ofDrawBitmapString(debugInfo, 10, 20);
}

bool ofApp::movePoint(vector<ofVec2f>& points, ofVec2f point) {
	for(int i = 0; i < points.size(); i++) {
		if(points[i].distance(point) < 20) {
			movingPoint = true;
			curPoint = &points[i];
			return true;
		}
	}
	return false;
}

void ofApp::mousePressed(int x, int y, int button) {
	ofVec2f cur(x, y);
	ofVec2f rightOffset(left.getWidth(), 0);
	if(!movePoint(leftPoints, cur) && !movePoint(rightPoints, cur)) {
		if(x > left.getWidth()) {
			cur -= rightOffset;
		}
		leftPoints.push_back(cur);
		rightPoints.push_back(cur + rightOffset);
	}
}

void ofApp::mouseDragged(int x, int y, int button) {
	if(movingPoint) {
		curPoint->set(x, y);
	}
}

void ofApp::mouseReleased(int x, int y, int button) {
	movingPoint = false;
}

void ofApp::keyPressed(int key) {
	if(key == ' ') {
		saveMatrix = true;
	}
	else if(key == 'm') {
		maskEnabled = !maskEnabled;
	} else if(key == 'r') {
		resetPoints();
	} else if(key == 'l') {
		loadPoints();
	}
}

void ofApp::resetPoints() {
	leftPoints.clear();
	rightPoints.clear();
	homographyReady = false;
}

void ofApp::loadPoints() {
	// load the previous homography if it's available
	ofFile previous("homography.txt");
	if(previous.exists()) {
		ofBuffer buffer = ofBufferFromFile("homography.txt");
		vector<string> lines = ofSplitString(buffer.getText(), "\n");
		if(lines.size() >= 16) {
			float values[16];
			for(int i = 0; i < 16; i++) {
				values[i] = ofToFloat(lines[i]);
			}
			homography = glm::make_mat4(values);
			homographyReady = true;
		}
	}
}
