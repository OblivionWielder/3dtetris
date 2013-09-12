/*
 * GLUT Shapes Demo
 * Eva Bojorges RodrÃ­guez 986896
 *Sergio Adrián Casas Fernandez 1033864
 */
#include <stdio.h>
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

using namespace std;
float  x = 25;
float  z = 0.5, y = 0.5;
const int medida = 1; // Mitad del tamaÃ±o de cada lado del cubo
bool borde[4] = {false};
bool choquePieza = false;
int puntos = 0;
int listaAEliminar[20]; //marca en 1 las lineas que se eliminaran
GLubyte label[6] = { 'S', 'C', 'O','R','E', ':'};
GLubyte gameover[40] = { 'G', 'A', 'M','E','O', 'V', 'E', 'R',' ','P', 'R', 'E', 'S','I','O','N', 'A', ' ','"','N','"', 'P', 'A','R','A',' ', 'J', 'U','G','A','R', ' ', 'D','E',' ','N', 'U', 'E','V','O'};
GLubyte eva[12] = { 'E', 'V', 'A',' ','B', 'O', 'J', 'O','R','G', 'E', 'S'};
GLubyte sergio[12] = { 'S', 'E', 'R','G','I', 'O', ' ', 'C','A','S', 'A', 'S'};
GLubyte mover[14] = { 'M', 'o', 'v','e','r', ':', ' ', 'W',',','A', ',', 'S', ',','D'};
GLubyte rotari[12] = { 'R', 'o', 't','a','r', ':', ' ', 'L',',','P', ',', 'O'};
GLubyte score[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
//matriz de ocupados
int lugaresOcupados[10][10][21] = {0};//x, z, y; y es 21 para poder detectar cuando una pieza este en 21 y por ende pierda

bool eje[3] = {true, true, true}; //DEPRECATED

//cubo usado para hacer las transformaciones
int cuboTrans[4][4][4] = {0}; //aqui pongo en una matriz mas pequenia la pieza a rotar
int transformacionMenor[3] = {99, 99, 99};//aqui pongo los desplazamientos en x, y Y z
int transformationsMayor[3] = {0};
bool pierde = false;
int color = 1;


// ambiente
GLfloat mat_ambient[][4] =
{
    {0.0215, 0.1745, 0.0215, 1.0},
    {0.135, 0.2225, 0.1575, 1.0},
    {0.05375, 0.05, 0.06625, 1.0},
    {0.25, 0.20725, 0.20725, 1.0},
    {0.1745, 0.01175, 0.01175, 1.0},
    {0.1, 0.18725, 0.1745, 1.0},
    
    {0.329412, 0.223529, 0.027451, 1.0},
    {0.2125, 0.1275, 0.054, 1.0},
    {0.25, 0.25, 0.25, 1.0},
    {0.19125, 0.0735, 0.0225, 1.0},
    {0.24725, 0.1995, 0.0745, 1.0},
    {0.19225, 0.19225, 0.19225, 1.0},
    
    {0.0, 0.0, 0.0, 1.0},
    {0.0, 0.1, 0.06, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    
    {0.02, 0.02, 0.02, 1.0},
    {0.0, 0.05, 0.05, 1.0},
    {0.0, 0.05, 0.0, 1.0},
    {0.05, 0.0, 0.0, 1.0},
    {0.05, 0.05, 0.05, 1.0},
    {0.05, 0.05, 0.0, 1.0}
};

// difusa
GLfloat mat_diffuse[][4] =
{
    {0.07568, 0.61424, 0.07568, 1.0},
    {0.54, 0.89, 0.63, 1.0},
    {0.18275, 0.17, 0.22525, 1.0},
    {1, 0.829, 0.829, 1.0},
    {0.61424, 0.04136, 0.04136, 1.0},
    {0.396, 0.74151, 0.69102, 1.0},
    
    {0.780392, 0.568627, 0.113725, 1.0},
    {0.714, 0.4284, 0.18144, 1.0},
    {0.4, 0.4, 0.4, 1.0},
    {0.7038, 0.27048, 0.0828, 1.0},
    {0.75164, 0.60648, 0.22648, 1.0},
    {0.50754, 0.50754, 0.50754, 1.0},
    
    {0.01, 0.01, 0.01, 1.0},
    {0.0, 0.50980392, 0.50980392, 1.0},
    {0.1, 0.35, 0.1, 1.0},
    {0.5, 0.0, 0.0, 1.0},
    {0.55, 0.55, 0.55, 1.0},
    {0.5, 0.5, 0.0, 1.0},
    
    {0.01, 0.01, 0.01, 1.0},
    {0.4, 0.5, 0.5, 1.0},
    {0.4, 0.5, 0.4, 1.0},
    {0.5, 0.4, 0.4, 1.0},
    {0.5, 0.5, 0.5, 1.0},
    {0.5, 0.5, 0.4, 1.0}
};

// especular
GLfloat mat_specular[][4] =
{
    {0.633, 0.727811, 0.633, 1.0},
    {0.316228, 0.316228, 0.316228, 1.0},
    {0.332741, 0.328634, 0.346435, 1.0},
    {0.296648, 0.296648, 0.296648, 1.0},
    {0.727811, 0.626959, 0.626959, 1.0},
    {0.297254, 0.30829, 0.306678, 1.0},
    
    {0.992157, 0.941176, 0.807843, 1.0},
    {0.393548, 0.271906, 0.166721, 1.0},
    {0.774597, 0.774597, 0.774597, 1.0},
    {0.256777, 0.137622, 0.086014, 1.0},
    {0.628281, 0.555802, 0.366065, 1.0},
    {0.508273, 0.508273, 0.508273, 1.0},
    
    {0.50, 0.50, 0.50, 1.0},
    {0.50196078, 0.50196078, 0.50196078, 1.0},
    {0.45, 0.55, 0.45, 1.0},
    {0.7, 0.6, 0.6, 1.0},
    {0.70, 0.70, 0.70, 1.0},
    {0.60, 0.60, 0.50, 1.0},
    
    {0.4, 0.4, 0.4, 1.0},
    {0.04, 0.7, 0.7, 1.0},
    {0.04, 0.7, 0.04, 1.0},
    {0.7, 0.04, 0.04, 1.0},
    {0.7, 0.7, 0.7, 1.0},
    {0.7, 0.7, 0.04, 1.0}
};

// brillo
GLfloat mat_shininess[][1] =
{
    {0.6}, {0.1}, {0.3}, {0.088}, {0.6}, {0.1},
    {0.21794872}, {0.2}, {0.6}, {0.1}, {0.4}, {0.4},
    {0.25}, {0.25}, {0.25}, {0.25}, {0.25}, {0.25},
    {0.078125}, {0.078125}, {0.078125}, {0.078125}, {0.078125}, {0.078125}
};



//matriz de posicion de pieza actual
int piezaActual[4][3]; //posiciones de cada uno de los cuadros 4 cuadros, 3 posiciones cada uno x,y,z
void moverXNegativo();
void moverYNegativo();
void moverZNegativo();
void moverZPositivo();
void moverXPositivo();
void moverYPositivo();



void reset()
{
    for (int x = 0; x < 4; x++)
    {
        
        for (int z = 0; z < 3; z++)
        {
            
            piezaActual[x][z]=0;
        }
    }
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            for (int z = 0; z < 10; z++)
            {
                lugaresOcupados[x][y][z] = 0;
                //repetir para la matriz de materiales
            }
        }
    }
    
    
    puntos=0;
    choquePieza = false;
    for (int x = 0; x < 20; x++)
    {
        listaAEliminar[x]=0;
        
    }
    
    pierde=false;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 14; x++)
        {
            for (int z = 0; z < 4; z++)
            {
                cuboTrans[x][y][z] = 0;
                //repetir para la matriz de materiales
            }
        }
    }
    for (int x = 0; x < 3; x++)
    {
        transformacionMenor[x]=99;
        
    }
    
    for (int x = 0; x < 3; x++)
    {
        transformationsMayor[x]=0;
        
    }
    
    for (int x = 0; x < 4; x++)
    {
        borde[x]=false;
        
    }


    
    
}

void material(int k) {
    //Asigna los apropiados materiales a las superficies
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient[k]);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[k]);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular[k]);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess[k]);
}

void pierdejuego()
{
    
    for (int x = 0; x < 10; x++)
    {
        
        for (int z = 0; z < 10; z++)
        {
            if (lugaresOcupados[x][z][20] == 1)
                pierde = true;
           
            
        }
        
    }
    
    
}


void marcaLineas()
{
    bool espacio = false;
    for (int y = 0; y < 21; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            if (!espacio)
            {
                for (int z = 0; z < 10; z++)
                {
                    if (lugaresOcupados[x][y][z] == 0)
                        espacio = true;
                }
            }
        }
        if(!espacio)
            listaAEliminar[y]=1; //marca esta fila para eliminarse
        espacio = false; //resetea y continua
    }
}

void bajarPiezas(int fila)
{
    for (int y = fila; y < 20; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            for (int z = 0; z < 10; z++)
            {
                lugaresOcupados[x][y][z] = lugaresOcupados[x][y+1][z];
                //repetir para la matriz de materiales
            }
        }
    }
}

void aplanar() //esta es la funcion principal para bajar y aplanar, se llama despues de marcarLineas
{
    for (int i = 0; i < 20; i++)
    {
        if(listaAEliminar[i] == 1)
        {
            bajarPiezas(i);
            puntos++;
        }
    }
}

void eliminaPlanos() //ESTA ES LA MERA MERA!! :D
{
    marcaLineas();
    aplanar();
}


void generaT()
{
    
    //parte de arriba del cuadro
    piezaActual[0][0]= 3;//x
    piezaActual[0][1]= 20;//y
    piezaActual[0][2]= 4;//z
    
    piezaActual[1][0]= 4;
    piezaActual[1][1]= 20;
    piezaActual[1][2]= 4;
    
    //parte de abajo del cuadro
    piezaActual[2][0]= 5;
    piezaActual[2][1]= 20;
    piezaActual[2][2]= 4;
    
    piezaActual[3][0]= 4;
    piezaActual[3][1]= 19;
    piezaActual[3][2]= 4;
}


void generaCuadro()
{
    //  **
    //  **
    //
    //
    
    //parte de arriba del cuadro
    piezaActual[0][0]= 4; //x
    piezaActual[0][1]= 20;//y
    piezaActual[0][2]= 3;//z
    
    piezaActual[1][0]= 5;
    piezaActual[1][1]= 20;
    piezaActual[1][2]= 3;
    
    //parte de abajo del cuadro
    piezaActual[2][0]= 4;
    piezaActual[2][1]= 19;
    piezaActual[2][2]= 3;
    
    piezaActual[3][0]= 5;
    piezaActual[3][1]= 19;
    piezaActual[3][2]= 3;
}

void generaBarra()
{
    //  *
    //  *
    //  *
    //  *
    
    //parte de arriba del cuadro
    piezaActual[0][0]= 4;//x
    piezaActual[0][1]= 20;//y
    piezaActual[0][2]= 4;//z
    
    piezaActual[1][0]= 4;
    piezaActual[1][1]= 19;
    piezaActual[1][2]= 4;
    
    //parte de abajo del cuadro
    piezaActual[2][0]= 4;
    piezaActual[2][1]= 18;
    piezaActual[2][2]= 4;
    
    piezaActual[3][0]= 4;
    piezaActual[3][1]= 17;
    piezaActual[3][2]= 4;
}

void generaEle()
{
    //  *
    //  *
    //  **
    //
    
    //parte de arriba del cuadro
    piezaActual[0][0]= 4;//x
    piezaActual[0][1]= 20;//y
    piezaActual[0][2]= 4;//z
    
    piezaActual[1][0]= 4;
    piezaActual[1][1]= 19;
    piezaActual[1][2]= 4;
    
    //parte de abajo del cuadro
    piezaActual[2][0]= 4;
    piezaActual[2][1]= 18;
    piezaActual[2][2]= 4;
    
    piezaActual[3][0]= 5;
    piezaActual[3][1]= 18;
    piezaActual[3][2]= 4;
}

void generaSnake()
{
    //  *
    //  **
    //   *
    //
    
    //parte de arriba del cuadro
    piezaActual[0][0]= 4;//x
    piezaActual[0][1]= 20;//y
    piezaActual[0][2]= 4;//z
    
    piezaActual[1][0]= 4;
    piezaActual[1][1]= 19;
    piezaActual[1][2]= 4;
    
    //parte de abajo del cuadro
    piezaActual[2][0]= 5;
    piezaActual[2][1]= 19;
    piezaActual[2][2]= 4;
    
    piezaActual[3][0]= 5;
    piezaActual[3][1]= 18;
    piezaActual[3][2]= 4;
}



void bajar()//baja la pieza, ya hubo verificacion anterior
{
    for(int i = 0; i < 4; i++)
    {
        piezaActual[i][1]=piezaActual[i][1]-1;
    }
}

void generaPieza()//genera una de las piezas que puedan existir en le tetris, simplemente asigna las coordenadas nuevas  a la matriz de pieza actual
{
    switch(color)
    {
        case 0:
            material(1);
            generaCuadro();
            break;
        case 1:
            material(6);
            generaBarra();
            break;
        case 2:
            material(3);
            generaEle();
            break;
        case 3:
            material(4);
            generaSnake();
            break;
        case 4:
            material(5);
            generaT();
            break;
        default:
            material(6);
            generaBarra();
            break;
    }
    
    
}
void mataYGenera()//esto quiere decir que si habia pieza.
{
    //pasa la pieza actual a la matriz de juego
    for(int i = 0; i < 4; i++)
    {
        lugaresOcupados[piezaActual[i][0]][piezaActual[i][2]][piezaActual[i][1]]=1;//X, Z, Y
    }
    //genera una nueva pieza de entre las posibles
    color = (rand()%5);
    generaPieza();
}
void cae() //se encarga de revisar si hay algo abajo de la pieza
{
    for(int i = 0; i < 4; i++)
    {
        //if((lugaresOcupados[piezaActual[i][0]][piezaActual[i][2]][piezaActual[i][1]-1] == 1) && !choquePieza)
        if(lugaresOcupados[piezaActual[i][0]][piezaActual[i][2]][piezaActual[i][1]-1] == 1)
        {
            //prender bandera de que colisionaste con pieza
            choquePieza = true;
        }
        
        //if(((piezaActual[i][1]-1) == -1) && !choquePieza) //si la Y quedara en -1 (fuera)
        if(((piezaActual[i][1]-1) == -1) && !choquePieza) //si la Y quedara en -1 (fuera)
        {
            choquePieza = true;
        }
        
    }
    if(!choquePieza)
    {
        bajar();
    }
    else
    {
        mataYGenera();
        choquePieza = false;
    }
    
}


void init(void)
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST); //para eliminar las caras ocultas
    glEnable(GL_NORMALIZE); //normaliza el vector para ombrear apropiadamente
    
    
    // asigna la apropiada fuente de luz
    GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat light_position[] = {1.0f, -2.0f, 5.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION,light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,lightIntensity);

    glClearColor (0.5, 0.7, 0.2, 0.0);
    glShadeModel (GL_SMOOTH);
    generaBarra();
}
void myTimer(int v)
{
    if(x > 10) x -= 10;
    
    //bajar();
    cae();
    eliminaPlanos();
    pierdejuego();
    glutPostRedisplay();
    glutTimerFunc(300,myTimer,1);
    //cout << x << " , ";
}

void reshape (int w, int h)
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(-10.0, 10, -10, 10, -10, 10);
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    // glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}





///rotaciones
// usar regla del pulgar apuntando a la parte positiva del eje

//.IDEA
/*
 llevar la pieza a coordenadas mas chicas dentro de un cubo centrandola
 guardar la transformacion/deslpazamiento
 rotar el cubo con posiciones conocidas
 devolver los desplazamientos
 http://cosmos.ucdavis.edu/archives/2011/cluster6/Hao_Steven.pdf
 */

//MODULO EXPERIMENTAL DE ROTACION
void averiguaEje()
{
    for(int i = 0; i < 3; i++)
    {
        if(piezaActual[i][0] != piezaActual[i+1][0])
            eje[0]=false;
        if(piezaActual[i][1] != piezaActual[i+1][1])
            eje[1]=false;
        if(piezaActual[i][2] != piezaActual[i+1][2])
            eje[2]=false;
    }
}


//OBTEN LOS MENORES
void getMenorX()
{
    for(int i = 0; i < 4; i++)
        if(transformacionMenor[0] > piezaActual[i][0])
            transformacionMenor[0] = piezaActual[i][0];
}

void getMenorY()
{
    for(int i = 0; i < 4; i++)
        if(transformacionMenor[1] > piezaActual[i][1])
            transformacionMenor[1] = piezaActual[i][1];
    
}

void getMenorZ()
{
    for(int i = 0; i < 4; i++)
        if(transformacionMenor[2] > piezaActual[i][2])
            transformacionMenor[2] = piezaActual[i][2];
}


int *get(int offset, int x, int y, int ejeRotar, int seccion)
//ejeRotar=x, 2=y, 3=z
{
    switch(ejeRotar)
    {
        case 1:
            return &cuboTrans[seccion][offset + x][offset + y];
            break;
            
        case 2:
            return &cuboTrans[offset + x][seccion][offset + y];
            break;
            
        case 3:
            return &cuboTrans[offset + x][seccion][offset + y];
            break;
            
        default:
            printf("NO ROTO NADA?!?!?!?\n");
            return &cuboTrans[offset + x][seccion][offset + y];
            break;
    }
    // return &cuboTrans[offset + x][offset + y];
}


void transpose(int offset, int n, int ejeRotar, int seccion) //ejeRotar=x, 2=y, 3=z
{
    if (n > 1) {
        for (int i = 0; i < n - 1; i++) {
            int *val1 = get(offset, 0, i, ejeRotar, seccion);
            int *val2 = get(offset, i, n - 1, ejeRotar, seccion);
            int *val3 = get(offset, n - 1, n - 1 - i, ejeRotar, seccion);
            int *val4 = get(offset, n - 1 - i, 0, ejeRotar, seccion);
            
            int temp = *val1;
            *val1 = *val4;
            *val4 = *val3;
            *val3 = *val2;
            *val2 = temp;
        }
        
        transpose(offset + 1, n - 2, ejeRotar, seccion);
    }
}


void rotar(int x, int y, int z)
{
    //recibe un 1 o 0 dependiendo de como queramos rotarlo sobre que eje
    
    
    //DEPRECATED
    //averiguamos sobre que eje esta
    // averiguaEje(); //1=x, 2=y, 3=z
    //END DEPRECATED
    
    
    //obtenemos los menores
    getMenorX();
    getMenorY();
    getMenorZ();
    
    //indice de seccion del cubo a rotar
    int seccion = 0;
    
    //traslada a un cubo de 4x4x4 la pieza para poderla transformar
    if(x)
        for(int i = 0; i < 4; i++)
        {
            //cout << (piezaActual[i][0])%transformacionMenor[0] << ",";
            //cout << (piezaActual[i][1])%transformacionMenor[1] << ",";
            //cout << (piezaActual[i][2])%transformacionMenor[2] << ", \n";
            
            //cuboTrans  [(piezaActual[i][0])%transformacionMenor[0]][(piezaActual[i][1])%transformacionMenor[1]][(piezaActual[i][2])%transformacionMenor[2]]=1;
            
            piezaActual[i][0] -= transformacionMenor[0] + 1;
            piezaActual[i][1] -= transformacionMenor[1] + 1;
            piezaActual[i][2] -= transformacionMenor[2] + 1;
            
            //cout << "- " << piezaActual[i][1] << ", " << piezaActual[i][2] << "\n";
            
            int temp = piezaActual[i][1];
            piezaActual[i][1] = -piezaActual[i][2];
            piezaActual[i][2] = temp;
            
            //cout << "+ " << piezaActual[i][1] << ", " << piezaActual[i][2] << "\n";
            
            piezaActual[i][0] += transformacionMenor[0] + 1;
            piezaActual[i][1] += transformacionMenor[1] + 1;
            piezaActual[i][2] += transformacionMenor[2] + 1;
        }
    else if(y)
        for(int i = 0; i < 4; i++)
        {
            //cout << (piezaActual[i][0])%transformacionMenor[0] << ",";
            //cout << (piezaActual[i][1])%transformacionMenor[1] << ",";
            //cout << (piezaActual[i][2])%transformacionMenor[2] << ", \n";
            
            //cuboTrans  [(piezaActual[i][0])%transformacionMenor[0]][(piezaActual[i][1])%transformacionMenor[1]][(piezaActual[i][2])%transformacionMenor[2]]=1;
            
            piezaActual[i][0] -= transformacionMenor[0] + 1;
            piezaActual[i][1] -= transformacionMenor[1] + 1;
            piezaActual[i][2] -= transformacionMenor[2] + 1;
            
            //cout << "- " << piezaActual[i][1] << ", " << piezaActual[i][2] << "\n";
            
            int temp = piezaActual[i][0];
            piezaActual[i][0] = -piezaActual[i][2];
            piezaActual[i][2] = temp;
            
            //cout << "+ " << piezaActual[i][1] << ", " << piezaActual[i][2] << "\n";
            
            piezaActual[i][0] += transformacionMenor[0] + 1;
            piezaActual[i][1] += transformacionMenor[1] + 1;
            piezaActual[i][2] += transformacionMenor[2] + 1;
        }
    else
        for(int i = 0; i < 4; i++)
        {
            //cout << (piezaActual[i][0])%transformacionMenor[0] << ",";
            //cout << (piezaActual[i][1])%transformacionMenor[1] << ",";
            //cout << (piezaActual[i][2])%transformacionMenor[2] << ", \n";
            
            //cuboTrans  [(piezaActual[i][0])%transformacionMenor[0]][(piezaActual[i][1])%transformacionMenor[1]][(piezaActual[i][2])%transformacionMenor[2]]=1;
            
            piezaActual[i][0] -= transformacionMenor[0] + 1;
            piezaActual[i][1] -= transformacionMenor[1] + 1;
            piezaActual[i][2] -= transformacionMenor[2] + 1;
            
            //cout << "- " << piezaActual[i][1] << ", " << piezaActual[i][2] << "\n";
            
            int temp = piezaActual[i][0];
            piezaActual[i][0] = -piezaActual[i][1];
            piezaActual[i][1] = temp;
            
            //cout << "+ " << piezaActual[i][1] << ", " << piezaActual[i][2] << "\n";
            
            piezaActual[i][0] += transformacionMenor[0] + 1;
            piezaActual[i][1] += transformacionMenor[1] + 1;
            piezaActual[i][2] += transformacionMenor[2] + 1;
        }
    /*
     cout << "before\n";
     
     for(int x = 0; x < 4; x++)
     for(int y = 0; y < 4; y++)
     for(int z = 0; z < 4; z++)
     if(cuboTrans[x][y][z] == 1)
     {
     cout << x << " " << y << " " << z << "\n";
     }
     
     //transformamos en sentido de las manesillas del reloj sobre ese eje
     if(x)
     {
     for (int i = 0; i < 4; ++i)
     transpose(0 + 1, 4 - 2, 1, i);
     
     }
     else if(y)
     {
     for (int i = 0; i < 4; ++i)
     transpose(0 + 1, 4 - 2, 2, i);
     }
     else if(z)
     {
     for (int i = 0; i < 4; ++i)
     transpose(0 + 1, 4 - 2, 3, i);
     }
     
     cout << "after\n";
     
     for(int x = 0; x < 4; x++)
     for(int y = 0; y < 4; y++)
     for(int z = 0; z < 4; z++)
     if(cuboTrans[x][y][z])
     {
     cout << x << " " << y << " " << z << "\n";
     }
     
     
     int cubito = 0;
     //REGRESAMOS LA MATRIZ RENGLON POR RENGLON COMO NUEVOS BLOQUES
     for(int x=0; x<4; x++)
     for(int y=0; y<4; y++)
     for(int z=0; z<4; z++)
     //recorre el cubo buscando los unos y asignagno los indices a la nueva piezaActual
     if(cuboTrans[x][y][z] == 1)
     {
     piezaActual[cubito][0]=x;
     piezaActual[cubito][1]=y;
     piezaActual[cubito][2]=z;
     cubito++;
     }
     //traslada los menores para una aproximacion a la posicion original
     for (int i = 0; i < 4; ++i)
     {
     piezaActual[i][0]=piezaActual[i][0]+transformacionMenor[0];
     piezaActual[i][1]=piezaActual[i][1]+transformacionMenor[1];
     piezaActual[i][2]=piezaActual[i][2]+transformacionMenor[2];
     
     }
     
     */
    
    //RESETEA VARIABLES USADAS
    memset(cuboTrans, 0, sizeof cuboTrans);
    //memset(transformacionMenor, 99, sizeof transformacionMenor);
    cuboTrans[4][4][4] = {0}; //aqui pongo en una matriz mas pequenia la pieza a rotar
    transformacionMenor[0] = 99;
    transformacionMenor[1] = 99;
    transformacionMenor[2] = 99;
    //cubito = 0;
    
}



//TERMINA MODULO EXPERIMENTAL DE ROTACION


//SOBRE EL EJE X
void rotarXpositivo()
{
    rotar(1,0,0);
}
void rotarXNegativo()
{
    rotar(1,0,0);
    rotar(1,0,0);
    rotar(1,0,0);
}

//SOBRE EL EJE Y
void rotarYPositivo()
{
    rotar(0,1,0);
}
void rotarYNegativo()
{
    rotar(0,1,0);
    rotar(0,1,0);
    rotar(0,1,0);
}

//SOBRE EL EJE Z
void rotarZPositivo()
{
    rotar(0,0,1);
}
void rotarZNegativo()
{
    rotar(0,0,1);
    rotar(0,0,1);
    rotar(0,0,1);
}




GLvoid
keyboard( GLubyte key, GLint gx, GLint gy )
{
    switch (key) {
        case 'd':
            y -= 1;
            moverZNegativo();
            break;
        case 'a':
            y += 1;
            moverZPositivo();
            break;
        case 'w':
            z -= 1;
            moverXNegativo();
            break;
        case 's':
            z += 1;
            moverXPositivo();
            break;
        case 'l':
            rotar(1,0,0);
            break;
        case 'p':
            rotar(0,1,0);
            break;
        case 'o':
            rotar(0,0,1);
            break;
        case 'n':
            reset();
            break;
        case 27:
            // esc
            exit(0);
    }
}


void moverZNegativo()
{
    for(int i = 0; i < 4; i++)
    {
        
        if(piezaActual[i][2]<0) //se paso por alguna rotacion probablemente y por eso lo movemos en negativo en su lugar
        {
            //muevelo para atras
            moverZPositivo();
            borde[3] = true;
        }
        else if(piezaActual[i][2]==0)
        {
            //no lo muevas e indica que esta en el borde
            borde[3] = true;
        }
        else
        {
            //no estas en el borde
            borde[3] = false;
        }
        
    }
    if(!borde[3])
    {
        for(int i = 0; i < 4; i++)
        {
            piezaActual[i][2]--;
        }
    }
    
}


void moverZPositivo()
{
    for(int i = 0; i < 4; i++)
    {
        
        if(piezaActual[i][2]>10) //se paso por alguna rotacion probablemente y por eso lo movemos en negativo en su lugar
        {
            //muevelo para atras
            moverZNegativo();
            borde[2] = true;
        }
        else if(piezaActual[i][2]==10)
        {
            //no lo muevas e indica que esta en el borde
            borde[2] = true;
        }
        else
        {
            //no estas en el borde
            borde[2] = false;
        }
        
    }
    if(!borde[2])
    {
        for(int i = 0; i < 4; i++)
        {
            piezaActual[i][2]++;
        }
    }
}


void moverXPositivo()
{
    for(int i = 0; i < 4; i++)
    {
        
        if(piezaActual[i][0]>10) //se paso por alguna rotacion probablemente y por eso lo movemos en negativo en su lugar
        {
            //muevelo para atras
            moverXNegativo();
            borde[0] = true;
        }
        else if(piezaActual[i][0]==10)
        {
            //no lo muevas e indica que esta en el borde
            borde[0] = true;
        }
        else
        {
            //no estas en el borde
            borde[0] = false;
        }
        
    }
    if(!borde[0])
    {
        for(int i = 0; i < 4; i++)
        {
            piezaActual[i][0]++;
        }
    }
    
}
void moverXNegativo()
{
    for(int i = 0; i < 4; i++)
    {
        
        if(piezaActual[i][0]<0) //se paso por alguna rotacion probablemente y por eso lo movemos en negativo en su lugar
        {
            //muevelo para atras
            moverXPositivo();
            borde[1] = true;
        }
        else if(piezaActual[i][0]==0)
        {
            //no lo muevas e indica que esta en el borde
            borde[1] = true;
        }
        else
        {
            //no estas en el borde
            borde[1] = false;
        }
        
    }
    if(!borde[1])
    {
        for(int i = 0; i < 4; i++)
        {
            piezaActual[i][0]--;
        }
    }
    
    
}


void dibuja() {
    
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //////////////////////////////////
    // RotaciÃ³n para que se aprecie en 3D, si no, se ve sÃ³lo una cara
    // Angulo de rotaciÃ³n = 45, rotando en X=1, Y=1, Z=0.
    
    glPushMatrix();
    glRotatef(45, 1.0, 0.0, 0.0);
    glRotatef(320, 0.0, 1.0, 0.0);
    
    glTranslatef(-5, -5, -5);
    glPushMatrix();
    //////////////////////////////////
    
    //x es derecha
    //y es arriba
    //z es izquierda
    
    
    //cout << "y:" << y << "\n";
    for(int i = 0; i < 4; i++){
        glPushMatrix();
        //glTranslatef(x, y, z);
        glTranslatef(.5, .5, .5);
        glTranslatef(piezaActual[i][0], piezaActual[i][1] , piezaActual[i][2]);
          material(color);
        glutSolidCube(1);
        glPopMatrix();
    }
    
    for(int i = 0; i < 10; i++){
        glPushMatrix();
        //glTranslatef(x, y, z);
        glTranslatef(.5, .5, .5);
        for(int j = 0; j < 10; j++){
            for(int k = 0; k < 20; k++){
                if(lugaresOcupados[i][j][k] == 1){
                    glPushMatrix();
                    glTranslatef(i, k, j);
                    material(7);
                    glutSolidCube(1);
                    glPopMatrix();
                }
                
            }}
        
        glRasterPos2f(7.0,-6.9);
        for (int i = 0; i < 6; i++)
        { glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, label[i]);
        }
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, score[puntos/10]);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, score[puntos%10]);

        glPopMatrix();
    }
    
    /*  glBegin(GL_QUADS);
     
     
     
     //Arriba (amarillo)
     glColor3f(1.0, 1.0, 0.0);
     glVertex3i( -medida, medida, -medida );
     glVertex3i( -medida, medida, medida );
     glVertex3i( medida, medida, medida );
     glVertex3i( medida, medida, -medida );
     
     //Abajo (magenta)
     glColor3f(1.0, 0.0, 1.0);
     glVertex3i( -medida, -medida, -medida );
     glVertex3i( medida, -medida, -medida );
     glVertex3i( medida, -medida, medida );
     glVertex3i( -medida, -medida, medida );
     
     //Izquierda (azules)
     glColor3f(0.0, 1.0, 1.0);
     glVertex3i( -medida, -medida, -medida );
     glVertex3i( -medida, -medida, medida );
     glColor3f(0.0, 0.0, 1.0);
     glVertex3i( -medida, medida, medida );
     glVertex3i( -medida, medida, -medida );
     
     //Derecha (rojo y verde)
     glColor3f(1.0, 0.0, 0.0);
     glVertex3i( medida, -medida, -medida );
     glVertex3i( medida, medida, -medida );
     glColor3f(0.0, 1.0, 0.0);
     glVertex3i( medida, medida, medida );
     glVertex3i( medida, -medida, medida );
     
     // Blanco
     glColor3f(1.0, 1.0, 1.0);
     
     //Frente blanco
     glVertex3i( -medida, -medida, medida );
     glVertex3i( medida, -medida, medida );
     glVertex3i( medida, medida, medida );
     glVertex3i( -medida, medida, medida );
     
     //AtrÃ¡s blanco
     glVertex3i( -medida, -medida, -medida );
     glVertex3i( -medida, medida, -medida );
     glVertex3i( medida, medida, -medida );
     glVertex3i( medida, -medida, -medida );
     
     
     glEnd();
     //*/
    //
    
    glPopMatrix();
    
    // draw shadow
    
/*    glBegin(GL_QUADS);
   // material(1);
    
    glVertex3i( -medida + z, 0, -medida + y );
    glVertex3i( -medida + z, 0, medida + y );
    glVertex3i( medida + z, 0, medida + y );
    glVertex3i( medida + z, 0, -medida + y );
    
    
    glEnd();
    */
    
    //material(5);
    
    glBegin(GL_LINES);
    for(int i=0; i<10; i=i+1)
    {
        //XZ
        glVertex3i(i, 0, 0);
        glVertex3i(i, 0, 10);
        glVertex3i(0, 0, i);
        glVertex3i(10, 0, i);
        //YZ
        
        glVertex3i(0, 0, i);
        glVertex3i(0, 21, i);
        
        
        glVertex3i(i, 0, 0);
        glVertex3i(i, 21, 0);
        
    }
    glEnd();
    glBegin(GL_LINES);
    
    for(int i=0; i<21; i=i+1)
    {
        
        
        
        //XY
        
        glVertex3i(0, i, 0);
        glVertex3i(10, i, 0);
        
        
        glVertex3i(0, i, 0);
        glVertex3i(0, i, 10);
        
        
    }
    glEnd();
    
    
    glPopMatrix();
    
    glRasterPos2f(-7.5, -9.1);
    for (int i = 0; i < 12; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, rotari[i]);
    }
    
    glRasterPos2f(0.5, -9.1);
    for (int i = 0; i < 14; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mover[i]);
    }
    // glFlush();
    

    if(pierde){
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clean the screen and the depth buffer
        //glLoadIdentity();									// Reset The Projection Matrix
        glRasterPos2f(-4.5, 1.0);
        for (int i = 0; i < 21; i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, gameover[i]);
        }
         glRasterPos2f(-4.5, -1.1);
        for (int i = 21; i < 40; i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, gameover[i]);
        }
        
        glRasterPos2f(-4.5, -3.1);
        for (int i = 0; i < 12; i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, eva[i]);
        }
        
        glRasterPos2f(-4.5, -5.1);
        for (int i = 0; i < 12; i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, sergio[i]);
        }
    }
    
        glutSwapBuffers();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutTimerFunc(300,myTimer,1);
    glutCreateWindow("Cubo de colores ");
    //Sistema de coordenadas en 3D
    glOrtho(-10.0, 10, -10, 10, -10, 10 ); //izq, der, abajo, arriba, cerca, lejos
    init();
    
    // Para que OpenGl reconozca la profundidad en el eje Z
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc( keyboard );
    glutMainLoop();
    return 0;
}
