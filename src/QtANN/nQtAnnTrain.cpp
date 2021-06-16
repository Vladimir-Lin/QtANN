#include <qtann.h>

QtAnnTrain:: QtAnnTrain  ( void         )
           : ErrNo       ( ANN::NoError )
           , ErrorString ( ""           )
           , num_data    ( 0            )
           , num_input   ( 0            )
           , num_output  ( 0            )
           , input       ( NULL         )
           , output      ( NULL         )
{
}

QtAnnTrain::~QtAnnTrain(void)
{
}
