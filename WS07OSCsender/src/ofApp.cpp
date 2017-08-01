#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sender.setup("127.0.0.1", 8888);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    ofxOscMessage m;
    switch (key) {
        case '1':
            m.setAddress("/number");
            m.addIntArg(1);
            sender.sendMessage(m);
            break;
        case '2':
            m.setAddress("/number");
            m.addIntArg(2);
            sender.sendMessage(m);
            break;
        case '3':
            m.setAddress("/number");
            m.addIntArg(3);
            sender.sendMessage(m);
            break;
        default:
            break;
    }
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
