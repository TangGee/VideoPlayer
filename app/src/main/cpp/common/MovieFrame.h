//
// Created by tlinux on 18-11-10.
//

#ifndef MYAPPLICATION6_MOVIEFRAME_H
#define MYAPPLICATION6_MOVIEFRAME_H


enum MovieFrameType {
    MOVIE_TYPE_AUDIO = 1, MOVIE_TYPE_VIDEO
};

// VideoFrame AudioFrame base class
class MovieFrame {
protected:

    float position;
    float duration;
public:
    MovieFrame(float position, float duration);

   virtual MovieFrameType getType() =0;

   virtual float setPosition(int position) {
       this->position = position;
   }

   virtual float setDuration(int duration) {
       this->duration = duration;
   }

   virtual float getPosition() const {
       return position;
   }

   virtual float getDuration() {
       return duration;
   }
};


#endif //MYAPPLICATION6_MOVIEFRAME_H
