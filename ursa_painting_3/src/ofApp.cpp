#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    robot.setName("Robot Controls");
    robot.add(bFreedrive.set("Freedrive Mode", false));
    
    panel.setup();
    panel.add(robot);
    
    // start the python script
    sThread.setup("scripts/ursa_udp_5.py", commandPort, dataPort, false);
    sThread.startThread(true);
    
    // start thread to communicate with the python script
    cThread.connect(commandPort, dataPort);
    cThread.startThread();
    
    // set the current tcp transformation
    cThread.ur.setTCP(vector<float> {0,0,-0.1,0,0,0} ); // down a decimeter
    

}

//--------------------------------------------------------------
void ofApp::update(){

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    
    // draw robot data to screen
    cThread.ur.drawSystemValues(10, 35, ofColor(150));
    
    panel.draw();
    
    // fps
    stringstream ss;
    ss << setprecision(3) << fixed << "App FPS: " << ofGetFrameRate() << "\t\t" << "Data FPS: " << cThread.ur.fps;
    ofDrawBitmapStringHighlight(ss.str(), 10, 20);
}

//--------------------------------------------------------------
void ofApp::exit() {

    cThread.closeConnections();
    cThread.stopThread();
    
    // stop running the py server
    sThread.stopThread();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'q') cThread.ur.send("q");
    if (key == OF_KEY_UP) {
        cThread.ur.send("movej(p[0,0.5,0.2,3.14,0,0])");
    }
    if (key == OF_KEY_DOWN) {
        cThread.ur.send("movej(p[0,0.5,0.1,2.4,2.4,2.4])");
    }
    if (key == 'f') {
        cThread.ur.send("teach_mode()\n");
    }
    


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

//    cThread.path.addPoint(ofVec3f(x, y, 0));

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
