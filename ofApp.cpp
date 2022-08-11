#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("openFrameworks");
	ofSetFrameRate(30);

	ofBackground(0);
	ofSetColor(255);
	ofNoFill();
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->font_size = 55;
	this->font.loadFont("fonts/msgothic.ttc", this->font_size, true, true, true);

	this->charactor_list = { 'A', 'B', 'C', 'D', 'E', 'F',
								'G', 'H', 'I', 'J', 'K', 'L',
								'M', 'N', 'O', 'P', 'Q', 'R',
								'S', 'T', 'U', 'V', 'W', 'X',
								'Y', 'Z', '!' };
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);
	ofRotateX(ofGetFrameNum() * 0.5);

	int sample_count = 60;
	ofColor color;
	for (int i = 0; i < 450; i++) {

		ofPushMatrix();
		ofRotateZ(ofRandom(360));
		ofRotateY(ofRandom(360));
		ofRotateX(ofRandom(360));

		auto z = ofRandom(250, 280);
		auto b = z > 265 ? 255 : ofMap(z, 265, 280, 172, 255);
		color.setHsb(ofRandom(255), 255, b);
		ofSetColor(color);

		ofPath path = this->font.getCharacterAsPoints(this->charactor_list[(int)ofRandom(this->charactor_list.size())], true, false);
		vector<ofPolyline> outline = path.getOutline();
		auto frame_param = (int)ofRandom(sample_count * 2) + ofGetFrameNum() * (int)ofRandom(1, 3);

		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			outline[outline_index] = outline[outline_index].getResampledByCount(sample_count);
			vector<glm::vec3> vertices = outline[outline_index].getVertices();

			ofBeginShape();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				glm::vec3 vertex = glm::vec3(this->font_size * 0.5, this->font_size * 0.5, z) + glm::vec3(vertices[vertices_index].x, vertices[vertices_index].y, vertices[vertices_index].z);

				if (frame_param % (sample_count * 2) < sample_count) {

					if (vertices_index < frame_param % sample_count) {

						ofVertex(vertex);
					}
				}
				else {

					if (vertices_index > frame_param % sample_count) {

						ofVertex(vertex);
					}
				}

				if (vertices_index == frame_param % sample_count) {

					ofFill();
					ofDrawCircle(vertex, 2);
					ofNoFill();
				}
			}
			ofEndShape();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}