#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

#define W 1280
#define H 720
#define MAXI 300000
#define MINI 0

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void mouseReleased(int x, int y, int button);
    float getAngle(ofVec2f a, ofVec2f b, ofVec2f c);
    float getArea(float side1, float side2, float side3, float side4, float angle1, float angle2);
    int getRank(vector<float> area);
    ofColor selectCol(float f, float min, float max);
    enum Status {WAIT, MORE3, MORE2, MORE1, CALC, RESULT, MAP};
    Status stat;
    int ranking, juni[MAXI+2];
    float angleABC, angleCDA, time, timeStamp, xd, yd;
    vector<ofVec2f> points;
    vector<float> side, area;
    vector<ofFbo> rectImg;
    ofxTrueTypeFontUC font;
};
