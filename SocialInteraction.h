#pragma once


#include <iostream>
#include <cstring>  // For strncpy or strncpy_s
#include <fstream>

using namespace std;

class SocialInteraction {
private:
    char postContent[256];
    Workout w;

    // Using a larger buffer to avoid overflow

public:
    SocialInteraction() {
        postContent[0] = '\0';  // Initialize the array to an empty string
    }

    // Function to create a post with a char array as input
    void createPost(const char* content) {
        // Safely copy the content to postContent, ensuring no overflow
        strncpy_s(postContent, content, sizeof(postContent) - 1);
        postContent[sizeof(postContent) - 1] = '\0';  // Ensure null-termination

        string inp;
        bool share = false;

        cout << "Do you want to share your fitness record too on social media?! (Yes/No)" << endl;
        cin >> inp;
        if (inp == "Yes") {
            share = true;
            cout << "Oh nice you are really social media person," << endl;
            cout << "Your workout details are as follows and posted on social media!" << endl;
            w.displayWorkouts();
            cout << endl;
        }
        else {
            share = false;
        }

        ofstream custome("SocialMedia.bin", ios::binary | ios::app);
        if (!custome) {
            cerr << "Failed to open file for writing." << endl;
            return;
        }

        // Write the entire object to the file
        custome.write((char*)this, sizeof(*this));
        cout << "Details successfully entered!" << endl;
        custome.close();

        cout << "Post created: " << postContent << (share ? " with fitness record." : ".") << endl;
    }

    void displayPosts() const {
        ifstream infile("SocialMedia.bin", ios::binary);
        if (!infile) {
            cerr << "Failed to open file for reading." << endl;
            return;
        }

        SocialInteraction post;
        cout << "Stored Posts:" << endl;
        while (infile.read((char*)&post, sizeof(post))) {
            cout << "Post: " << post.postContent << endl;
        }

        infile.close();
    }
};

