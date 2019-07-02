#ifndef encoder_h
#define encoder_h

static unsigned long int intr_count_l=0;
static unsigned long int intr_count_r=0;



class encoder_class{
  private:

    unsigned long int count_l=0;
    unsigned long int count_r=0;

  static void int_left();
  static void int_right();

  public:

    void SETUP();
    void getPulsesLeft(unsigned long int *count_l);
    void getPulsesRight(unsigned long int *count_r);
    void getPulsesLeft_no_reset(unsigned long int *count_l);
    void getPulsesRight_no_reset(unsigned long int *count_r);

    void resetEncoderValues();

    void goDistanceForward(unsigned long int count);
    void goDistanceReverse(unsigned long int count);
    void goDistanceRight(unsigned long int count);
    void goDistanceLeft(unsigned long int count);

};

extern encoder_class encoder;

#endif
