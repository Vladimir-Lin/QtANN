#include <qtann.h>

QtAnnNeuron:: QtAnnNeuron( void         )
            : first      ( 0            )
            , last       ( 0            )
            , sum        ( 0            )
            , value      ( 0            )
            , steepness  ( 0            )
            , function   ( ANN::Nothing )
{
}

QtAnnNeuron::~QtAnnNeuron(void)
{
}
