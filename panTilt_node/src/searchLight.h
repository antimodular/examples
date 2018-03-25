//
//  searchLight.h
//  ofNodeExample
//
//  Created by Stephan Schulz on 2018-02-26.
//

#ifndef searchLight_h
#define searchLight_h

class searchLight{
public:
    
    float panValue,tiltValue;
    
    void setup(){
        
        heightOffGroud = 200;
        material.setDiffuseColor(ofFloatColor::green);
        
        boxBody.setPosition(0,0,0);
        boxBody2.setPosition(0,0,0);
        
        lightPost.set(10,heightOffGroud);
        lightPost.setPosition(0,heightOffGroud/2,0);;

    }
    
  
    
    void update(){

    }
    
    void draw(){
        
        ofMatrix4x4 translationMatrix;
        translationMatrix.makeTranslationMatrix(0,heightOffGroud,0);
        
        ofMatrix4x4 rotation_pan;
        rotation_pan.makeRotationMatrix(panValue,0,1,0);
        
        ofMatrix4x4 rotation_tilt;
        rotation_tilt.makeRotationMatrix(tiltValue,0,0,1);

        ofMatrix4x4 main_matrix;
        main_matrix = rotation_tilt * rotation_pan * translationMatrix;
        
        ofPoint pp1(0,0,0);
        ofPoint pp2(1000,0,0); 
        
        pp1 = pp1 * main_matrix;
        pp2 = pp2 * main_matrix;
        
        ofSetColor(255);
        ofDrawLine(pp1,pp2);
        
        material.begin();
        ofPushMatrix();
        ofTranslate(0,heightOffGroud,0);
        
        ofRotateDeg(panValue,0,1,0);
        ofRotateDeg(tiltValue,0,0,1);
        
        boxBody.draw();
        
               
        ofPopMatrix();
        material.end();
        
        lightPost.draw();
        
        //        headLight.draw();
        ofVec3f p1 = boxBody.getGlobalPosition();
        ofVec3f p2 = boxBody.getGlobalPosition() + (boxBody.getLookAtDir() * 1000);
//        ofDrawLine(p1,p2);
        
        lookAtNode.draw();
        
        //static reference
        ofPushMatrix();
        ofTranslate(0,heightOffGroud,0);
        ofSetColor(0);
        boxBody2.drawWireframe();
        ofPopMatrix();
        
          ofSetColor(255);
        ofDrawBitmapString("getLookAtDir "+ofToString(boxBody.getLookAtDir()),200,200);
        ofDrawBitmapString("getHeading "+ofToString(boxBody.getHeading()),200,220);
        ofDrawBitmapString("axisX "+ofToString(boxBody.getXAxis()),200,240);
        ofDrawBitmapString("axisY "+ofToString(boxBody.getYAxis()),200,260);
        ofDrawBitmapString("axisZ "+ofToString(boxBody.getZAxis()),200,280);

    }
    
    
    void rotateHorizontal(float dir){
//        boxBody.rotateDeg(dir,0,1,0);
//        boxBody.pan(dir);
        panValue += dir;
    }
    void rotateVertical(float dir){
//        boxBody.rotateDeg(dir, 1, 0, 0);
//        boxBody.tilt(dir);
        tiltValue += dir;
    }
    
private:
   
    ofBoxPrimitive boxBody;
    ofBoxPrimitive boxBody2;
    
    ofCylinderPrimitive lightPost;
    ofMaterial material;

    ofNode lookAtNode;
    float heightOffGroud;
};

#endif /* searchLight_h */
