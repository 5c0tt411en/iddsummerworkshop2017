#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    stat = WAIT;
    glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA,GL_ONE);
    ofSetLineWidth(15.0);
    ofEnableSmoothing();
    font.load("fonts/NotoSansCJKjp-Regular.otf", 30);
}

//--------------------------------------------------------------
void ofApp::update(){
    switch (stat) {
        case WAIT:
            if (points.size() == 1) {
                stat = MORE3;
                timeStamp = ofGetElapsedTimef();
            }
            break;
        case MORE3:
            if (points.size() == 2) {
                stat = MORE2;
                timeStamp = ofGetElapsedTimef();
            }
            if (time > 30) {
                stat = WAIT;
                timeStamp = ofGetElapsedTimef();
                points.clear();
            }
            break;
        case MORE2:
            if (points.size() == 3) {
                stat = MORE1;
                timeStamp = ofGetElapsedTimef();
            }
            if (time > 30) {
                stat = WAIT;
                timeStamp = ofGetElapsedTimef();
                points.clear();
            }
            break;
        case MORE1:
            if (points.size() == 4) {
                stat = CALC;
                timeStamp = ofGetElapsedTimef();
            }
            if (time > 30) {
                stat = CALC;
                timeStamp = ofGetElapsedTimef();
                points.clear();
            }
            break;
        case CALC:
            for (int i = 0; i < points.size(); i++) {
                if (i == 3) side.push_back(ofDist(points[i].x, points[i].y, points[0].x, points[0].y));
                else side.push_back(ofDist(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y));
            }
            
            // ３辺のなす角を求める
            angleABC = getAngle(points[0], points[1], points[2]);
            angleCDA = getAngle(points[2], points[3], points[0]);
            // ４辺の長さと向かい角から四角形の面積を求める
            area.push_back(getArea(side[0], side[1], side[2], side[3], angleABC, angleCDA));
            // すべての四角形を順位付けする
            ranking = getRank(area);
            
            stat = RESULT;
            timeStamp = ofGetElapsedTimef();
            break;
        case RESULT:
            stat = MAP;
            timeStamp = ofGetElapsedTimef();
            break;
        case MAP:
            if (time >= 5.0) {
                points.clear();
                side.clear();
                stat = WAIT;
                timeStamp = ofGetElapsedTimef();
            }
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofFbo cap;
    cap.allocate(1280, 720, GL_RGBA);
    ofSetColor(122);
    ofDrawRectangle(1280, 0, 1280, 720);
    time = ofGetElapsedTimef() - timeStamp;
    string s;
    switch (stat) {
        case WAIT:
            ofSetColor(0);
            font.drawString("面積が300000[px x px]の四角形を４点クリックして作ってください", 20, 50);
            break;
        case MORE3:
            ofSetColor(0);
            font.drawString("あと３点クリックしてください", 20, 50);
            break;
        case MORE2:
            ofSetColor(0);
            font.drawString("あと２点クリックしてください", 20, 50);
            break;
        case MORE1:
            ofSetColor(0);
            font.drawString("あと１点クリックしてください", 20, 50);
            break;
        case CALC:
            break;
        case RESULT:
            break;
        case MAP:
            ofSetColor(0);
            s = "面積は" + ofToString(area.back()) + "です" + '\n';
            if (area.back() <= MAXI) s += "暫定" + ofToString(ranking) + "位です" + '\n';
            else s += "300000を越えたため失格です";
            font.drawString(s, 20, 50);
            break;
        default:
            break;
    }
    
    if (stat == RESULT) {
        cap.begin();
        ofClear(255, 255, 255, 0);
    }
    // infographics
    if (side.size()) {
        ofSetColor(selectCol(side[0], 0, sqrt(W * W + H * H)));
        ofDrawRectangle(0, H, W / 7, -ofMap(side[0], 0, sqrt(W * W + H * H), 0, H));
        ofSetColor(selectCol(side[1], 0, sqrt(W * W + H * H)));
        ofDrawRectangle(W / 7, H, W / 7, -ofMap(side[1], 0, sqrt(W * W + H * H), 0, H));
        ofSetColor(selectCol(side[2], 0, sqrt(W * W + H * H)));
        ofDrawRectangle(2 * W / 7, H, W / 7, -ofMap(side[2], 0, sqrt(W * W + H * H), 0, H));
        ofSetColor(selectCol(side[3], 0, sqrt(W * W + H * H)));
        ofDrawRectangle(3 * W / 7, H, W / 7, -ofMap(side[3], 0, sqrt(W * W + H * H), 0, H));
        ofSetColor(selectCol(angleABC, 0, 180));
        ofDrawRectangle(4 * W / 7, H, W / 7, -ofMap(angleABC, 0, 180, 0, H));
        ofSetColor(selectCol(angleCDA, 0, 180));
        ofDrawRectangle(5 * W / 7, H, W / 7, -ofMap(angleCDA, 0, 180, 0, H));
        ofSetColor(selectCol(area.back(), 0, 300000));
        ofDrawRectangle(6 * W / 7, H, W / 7, -ofMap(area.back(), 0, 300000, 0, H));
    }
    ofSetColor(0);
    for (int i = 0; i < points.size(); i++) {
        ofDrawCircle(points[i].x, points[i].y, 10);
        if (i < points.size() - 1) {
            ofDrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
    }
    if (points.size() == 4) ofDrawLine(points[3].x, points[3].y, points[0].x, points[0].y);
    
    if (stat == RESULT) {
        cap.end();
        ofSetColor(255);
        cap.draw(0, 0);
        rectImg.push_back(cap);
    }
    
    for (int i = rectImg.size() - 1; i >= 0; i--) {
        xd = (rectImg.size() - i - 1) * W / 5;
        yd = 0;
        if (xd >= 4 * W) {
            xd -= 4 *  W;
            yd += 4 * H / 5;
        }
        else if (xd >= 3 * W) {
            xd -= 3 *  W;
            yd += 3 * H / 5;
        }
        else if (xd >= 2 * W) {
            xd -= 2 * W;
            yd += 2 * H / 5;
        }
        else if (xd >= W) {
            xd -= W;
            yd += H / 5;
        }
        
        ofSetColor(255);
        ofPushMatrix();
        ofTranslate(1280 + xd, yd);
        ofScale(0.2, 0.2);
        rectImg[i].draw(0, 0);
        ofPopMatrix();
    }
    if (rectImg.size() >= 27) {
        rectImg.erase(rectImg.begin());
        area.erase(area.begin());
    }
}

float ofApp::getAngle(ofVec2f a, ofVec2f b, ofVec2f c) {
    float ba0 = a.x - b.x;
    float ba1 = a.y - b.y;
    float bc0 = c.x - b.x;
    float bc1 = c.y - b.y;
    float babc = ba0 * bc0 + ba1 * bc1;
    float ban = (ba0 * ba0) + (ba1 * ba1);
    float bcn = (bc0 * bc0) + (bc1 * bc1);
    return acos(babc / (sqrt(ban * bcn))) * 180 / PI;
}

float ofApp::getArea(float side1, float side2, float side3, float side4, float angle1, float angle2) {
    float ar = (side1 + side2 + side3 + side4) / 2;
    float theta = angle1 + angle2;
    return sqrt((ar - side1) * (ar - side2) * (ar - side3) * (ar - side4) - side1 * side2 * side3 * side4 * ((1 + cos(theta * PI / 180)) / 2));
}

int ofApp::getRank(vector<float> area) {
    for(int i=MINI; i<=MAXI; i++) {
        juni[i]=0;
    }
    for(int i = 0; i < area.size(); i++) {
        juni[int(area[i])]++;
    }
    juni[MAXI+1]=1;
    for(int i=MAXI; i>=MINI; i--) {
        juni[i] = juni[i+1] + juni[i];
    }
    return juni[int(area.back()+1)];
}

ofColor ofApp::selectCol(float f, float min, float max) {
    ofColor col;
    f = ofMap(f, min, max, 0, 255);
    float c = 255 / 7;
    if (f >= 0 && f < c) col = ofColor(237,248,251);
    else if (f >= c && f < 2 * c) col = ofColor(191,211,230);
    else if (f >= 2 * c && f < 3 * c) col = ofColor(158,188,218);
    else if (f >= 3 * c && f < 4 * c) col = ofColor(140,150,198);
    else if (f >= 4 * c && f < 5 * c) col = ofColor(140,107,177);
    else if (f >= 4 * c && f < 6 * c) col = ofColor(136,65,157);
    else if (f >= 5 * c && f < 7 * c) col = ofColor(110,1,107);
    return col;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (x < 1280 && (stat == WAIT || stat == MORE3 || stat == MORE2 || stat == MORE1)) {
        points.push_back(ofVec2f(x, y));
    }
}

