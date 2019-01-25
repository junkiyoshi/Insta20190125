#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofNoFill();
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	int span = 144;
	for (int x = span * 0.5; x < ofGetWidth(); x += span) {

		for (int y = span * 0.5; y < ofGetHeight(); y += span) {

			ofPushMatrix();
			ofTranslate(x, y);
			ofRotateDeg(ofRandom(360));

			int radius = 60;
			int deg_span = 1;
			float noise_seed = ofRandom(1000);
			vector<int> degs;
			for (int deg = 0; deg < 180; deg += deg_span) {

				float noise_value = ofNoise((noise_seed + deg) * 0.04, ofGetFrameNum() * 0.01);
				if (noise_value > 0.4) {

					degs.push_back(deg);
				}
				else {

					if (degs.size() > 0) {

						vector<ofPoint> vertices;
						for (int i = 0; i < degs.size(); i++) {

							vertices.push_back(ofPoint(radius * cos(degs[i] * DEG_TO_RAD), radius * sin(degs[i] * DEG_TO_RAD)));
						}

						for (int i = degs.size() - 1; i >= 0; i--) {

							vertices.push_back(ofPoint(radius * cos((360 - degs[i]) * DEG_TO_RAD), radius * sin((360 - degs[i]) * DEG_TO_RAD)));
						}

						ofBeginShape();
						ofVertices(vertices);
						ofEndShape(true);

						degs.clear();
					}
				}
			}

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}