#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    stat = s01;
    sound.load("sound/sound.wav");
    video.load("video/video.mov");
}

//--------------------------------------------------------------
void ofApp::update(){
    switch (stat) {
        case s01:
            if (time >= 1.0) {
                sound.play();
                stat = s02;
                timeStamp = ofGetElapsedTimef();
            }
            break;
        case s02:
            if (time >= 2.0) {
                video.play();
                stat = s03;
                timeStamp = ofGetElapsedTimef();
            }
            break;
        case s03:
            video.update();
            if (time >= 4.0) {
                video.stop();
                stat = s01;
                timeStamp = ofGetElapsedTimef();
            }
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    time = ofGetElapsedTimef() - timeStamp;
    switch (stat) {
        case s01:
            break;
        case s02:
            break;
        case s03:
            video.draw(0, 0);
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
