//
//  oneTestPoint.h
//  flag_bacon
//
//  Created by Stephan Schulz on 2019-04-18.
//

#ifndef oneTestPoint_h
#define oneTestPoint_h

#include "nearest.h"

//one real world reference point 3 distances to 3 tripod points

class oneTestPoint{
  
private:
    
public:
    
    string label;
    
    vector<vector<ofPoint>> intersectionPerCircle;
    
    vector<ofPoint> intersections;
    vector<float> distances;
    
    vector<ofColor> tripod_colors;
    
    ofPoint bestIntersection;
    
    ofPolyline circlePolyline;
    vector<glm::vec3> circlePoints;
    ofPath path;
    
    void setup(){

        int res = 200;
        
        circlePolyline.clear();
        circlePolyline.arc(0,0,0,1,1,0,360,res);
        circlePoints.resize(circlePolyline.size());
        path.setCircleResolution(res);

    }
    
    void drawInfo(){
    
        int tempX = 100;
        int tempY = 50;
         ofDrawBitmapStringHighlight(label, tempX,tempY+=20);
         ofDrawBitmapStringHighlight(ofToString(distances[0])+" , "+ofToString(distances[1])+" ,"+ofToString(distances[2]), tempX,tempY+=20);
    }
    void draw(vector<ofPoint> _tripots, bool _showSphere){        
        //https://forum.openframeworks.cc/t/intersection-of-2-polylines/15785/2?u=stephanschulz
        drawPair(_tripots, 0, 1, _showSphere);
        drawPair(_tripots, 0, 2, _showSphere);
        drawPair(_tripots, 1, 2, _showSphere);
        
      
    }
  
    void drawPair(vector<ofPoint> _tripots, int a, int b, bool _showSphere){
        if(_showSphere){
            
            float alpha  = 150; //ofMap(ofGetElapsedTimeMillis()%1000,0,1000,0,255);
            ofPushMatrix();
            ofTranslate(_tripots[a]);
            ofSetColor(tripod_colors[a],alpha);
            ofDrawSphere(0,0,0,distances[a]);
            ofSetColor(0);
            ofDrawBitmapString(ofToString(a), 0, 0, 0);
            ofPopMatrix();
            
            ofPushMatrix();
            ofTranslate(_tripots[b]);
            ofSetColor(tripod_colors[b],alpha);
            ofDrawSphere(0,0,0,distances[b]);
            ofSetColor(0);
            ofDrawBitmapString(ofToString(b), 0, 0, 0);
            ofPopMatrix();
            
        }else{
            
            ofPushMatrix();
            ofTranslate(_tripots[a]);
            ofSetColor(tripod_colors[a],150);
            ofSetColor(0);
            ofDrawBitmapString(ofToString(a), 0, 0, 0);
            ofPopMatrix();
            
            ofPushMatrix();
            ofTranslate(_tripots[b]);
            ofSetColor(tripod_colors[b],150);
            ofSetColor(0);
            ofDrawBitmapString(ofToString(b), 0, 0, 0);
            ofPopMatrix();
            
        }
        
        
        ofSetLineWidth(3);
        ofPolyline pLine_0;
        getSphereSphereIntersection(_tripots[a],_tripots[b],distances[a],distances[b], pLine_0);
        
        ofFill();
        pLine_0.draw();
        ofSetLineWidth(1);
    }
      //-------------sphere intersection----------------  
    
    void getSphereSphereIntersection(ofPoint _sphere0, ofPoint _sphere1, float _r0, float _r1, ofPolyline &finalP){
        //http://mathworld.wolfram.com/Sphere-SphereIntersection.html
        
//        ofLog()<<"_sphere0 "<<_sphere0<<" _sphere1 "<<_sphere1;
        // https://forum.openframeworks.cc/t/rotate-ofvec3f-with-forward-and-up-vectors/12093
        
        float dist = _sphere1.distance(_sphere0); //this will basically make it so that one sphere is thought to be at zero and the other offset only in one direction, x
        ofVec3f differenceVec =  _sphere1 - _sphere0;
        ofVec3f forwardVec = differenceVec.getNormalized(); //direction
        
        ofMatrix4x4 rotMat;
        rotMat.makeRotationMatrix(ofVec3f(0,0,1), forwardVec); //_sphere0, _sphere1);
        
              
        //        _sphere1 = _sphere1 - _sphere0; //this makes _sphere0 be the origin and places _sphere1 in reference to it
        float d  = dist; //differenceVec.x;
//        ofLog()<<"_sphere1.x "<<_sphere1.x<<" _r0 "<<_r0<<" _r1 "<<_r1;
        float R = _r0;
        float r = _r1;
        float x = (d*d) - (r*r) + (R*R);
        x = x / (2 * d);
        
        //get circle radius
        float a = 1 / (2*d);
        float b = 4 * (d*d) * (R*R);
        float c = pow((d*d) - (r*r) + (R*R),2);
        float radius = a * sqrt( b - c );
//        ofLog()<<"at x "<<x<<" radius "<<d;

        
        ofVec3f intersectCircleCenter = _sphere0+ (forwardVec * x);
        
        ofMatrix4x4 transMat;
        transMat.makeTranslationMatrix(intersectCircleCenter);

        
        ofMatrix4x4 mainMat;
        mainMat = rotMat * transMat;


        ofPushMatrix();
        ofMultMatrix(mainMat);
        ofNoFill();
        ofSetLineWidth(2);
        ofSetColor(0);
//        ofDrawCircle(0,0,radius);
        //        ofDrawSphere(0,0,5);
//        circlePolyline.draw();
        ofPopMatrix();
        

        const auto & circleCache = circlePolyline.getVertices();
        for(size_t i=0;i<circleCache.size();i++){
            circlePoints[i] = {radius*circleCache[i].x,radius*circleCache[i].y,circleCache[i].z};
            circlePoints[i] = ofPoint(circlePoints[i]) * mainMat;
            finalP.addVertex(circlePoints[i]);
        }

         ofSetColor(0,0,255);
        ofDrawSphere(intersectCircleCenter,2);
        
    }
    
    
  //-------------circle intersection----------------  
  
    void getIntersections(vector<ofPoint> _tripots){
        
        intersectionPerCircle.clear();
        intersectionPerCircle.resize(3);
        double x3, y3, x3_prime, y3_prime;
        
        
        
        circle_circle_intersection(_tripots[0].x,_tripots[0].y, distances[0], 
                                   _tripots[1].x,_tripots[1].y, distances[1],
                                   &x3, &y3, &x3_prime, &y3_prime);
        
        intersections.push_back(ofPoint(x3,y3));
        intersections.push_back(ofPoint(x3_prime,y3_prime));
        intersectionPerCircle[0].push_back(ofPoint(x3,y3));
        intersectionPerCircle[0].push_back(ofPoint(x3_prime,y3_prime));
        
        intersectionPerCircle[1].push_back(ofPoint(x3,y3));
        intersectionPerCircle[1].push_back(ofPoint(x3_prime,y3_prime));
        
        
        circle_circle_intersection(_tripots[0].x,_tripots[0].y, distances[0], 
                                   _tripots[2].x,_tripots[2].y, distances[2],
                                   &x3, &y3, &x3_prime, &y3_prime);
        
        intersections.push_back(ofPoint(x3,y3));
        intersections.push_back(ofPoint(x3_prime,y3_prime));
        intersectionPerCircle[0].push_back(ofPoint(x3,y3));
        intersectionPerCircle[0].push_back(ofPoint(x3_prime,y3_prime));
        
        intersectionPerCircle[2].push_back(ofPoint(x3,y3));
        intersectionPerCircle[2].push_back(ofPoint(x3_prime,y3_prime));
        
        circle_circle_intersection(_tripots[1].x,_tripots[1].y, distances[1], 
                                   _tripots[2].x,_tripots[2].y, distances[2],
                                   &x3, &y3, &x3_prime, &y3_prime);
        
        intersections.push_back(ofPoint(x3,y3));
        intersections.push_back(ofPoint(x3_prime,y3_prime));
        intersectionPerCircle[1].push_back(ofPoint(x3,y3));
        intersectionPerCircle[1].push_back(ofPoint(x3_prime,y3_prime));
        
        intersectionPerCircle[2].push_back(ofPoint(x3,y3));
        intersectionPerCircle[2].push_back(ofPoint(x3_prime,y3_prime));
        
        
        //        nearest.nearestN(intersections,3,);
        
    }
    
  
    
    //http://paulbourke.net/geometry/circlesphere/tvoght.c
    //http://mathworld.wolfram.com/Circle-CircleIntersection.html
    /* circle_circle_intersection() *
     * Determine the points where 2 circles in a common plane intersect.
     *
     * int circle_circle_intersection(
     *                                // center and radius of 1st circle
     *                                double x0, double y0, double r0,
     *                                // center and radius of 2nd circle
     *                                double x1, double y1, double r1,
     *                                // 1st intersection point
     *                                double *xi, double *yi,              
     *                                // 2nd intersection point
     *                                double *xi_prime, double *yi_prime)
     *
     * This is a public domain work. 3/26/2005 Tim Voght
     *
     */

    
    int circle_circle_intersection(double x0, double y0, double r0,
                                   double x1, double y1, double r1,
                                   double *xi, double *yi,
                                   double *xi_prime, double *yi_prime)
    {
        double a, dx, dy, d, h, rx, ry;
        double x2, y2;
        
        /* dx and dy are the vertical and horizontal distances between
         * the circle centers.
         */
        dx = x1 - x0;
        dy = y1 - y0;
        
        /* Determine the straight-line distance between the centers. */
        //d = sqrt((dy*dy) + (dx*dx));
        d = hypot(dx,dy); // Suggested by Keith Briggs
        
        /* Check for solvability. */
        if (d > (r0 + r1))
        {
            /* no solution. circles do not intersect. */
            return 0;
        }
        if (d < fabs(r0 - r1))
        {
            /* no solution. one circle is contained in the other */
            return 0;
        }
        
        /* 'point 2' is the point where the line through the circle
         * intersection points crosses the line between the circle
         * centers.  
         */
        
        /* Determine the distance from point 0 to point 2. */
        a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d) ;
        
        /* Determine the coordinates of point 2. */
        x2 = x0 + (dx * a/d);
        y2 = y0 + (dy * a/d);
        
        /* Determine the distance from point 2 to either of the
         * intersection points.
         */
        h = sqrt((r0*r0) - (a*a));
        
        /* Now determine the offsets of the intersection points from
         * point 2.
         */
        rx = -dy * (h/d);
        ry = dx * (h/d);
        
        /* Determine the absolute intersection points. */
        *xi = x2 + rx;
        *xi_prime = x2 - rx;
        *yi = y2 + ry;
        *yi_prime = y2 - ry;
        
        return 1;
    }
    

};
#endif /* oneTestPoint_h */
