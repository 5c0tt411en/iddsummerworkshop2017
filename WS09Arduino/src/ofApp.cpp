#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ard.connect("/dev/cu.usbmodem14111", 57600);
    
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino	= false;
}

//--------------------------------------------------------------
void ofApp::update(){
    updateArduino();
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (!bSetupArduino){
        ofDrawBitmapStringHighlight("arduino not ready...\n", 20, 20);
    } else {
        ofDrawBitmapStringHighlight("arduino ready!", 20, 20);
    }
    
    ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, ard.getAnalog(0));
}

void ofApp::setupArduino(const int & version) {
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = true;
    
    ard.sendAnalogPinReporting(0, ARD_ANALOG);
}

void ofApp::updateArduino(){
   ard.update();
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
