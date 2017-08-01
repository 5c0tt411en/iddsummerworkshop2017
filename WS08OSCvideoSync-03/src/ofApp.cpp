#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    receiver.setup(10003);
    video.load("video/video.mov");
    stat = s01;
}

//--------------------------------------------------------------
void ofApp::update(){
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage message;
        receiver.getNextMessage(message);
        input = message.getArgAsInt32(0);
    }
    switch (stat) {
        case s01:
            if (input == 1) {
                video.play();
                stat = s02;
                timeStamp = ofGetElapsedTimef();
            }
            break;
        case s02:
            video.update();
            if (time >= 8.0) {
                video.stop();
                stat = s01;
                timeStamp = ofGetElapsedTimef();
                input = 0;
            }
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
