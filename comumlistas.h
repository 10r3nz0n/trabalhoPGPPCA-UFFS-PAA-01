#ifndef COMUMLISTAS_H
#define COMUMLISTAS_H

#define TIPO_CHAR   'C'
#define TIPO_INT    'I'
#define TIPO_FLOAT  'F'
#define TIPO_STRING 'S'

#define TRUE  1
#define FALSE 0

int  comumListasListaTipoEhValido   (char tipo);
void comumListasMostrarValor        (char tipo,  const void *valor);

#endif