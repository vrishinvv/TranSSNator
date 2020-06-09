#include <windows.h>
#include <string.h>
#include <stdio.h>

#define N1 12
#define N2 24

char vowe[N1][20][20];
char cone[N2][20][20];
char vowt[N1][20][20];
char cont[N2][20][20];
char mate[N2+1][N1+1][20][20];
char matt[N2+1][N1+1][20][20];
int cv=0,cc=0;


HWND hWndEdit1;
HWND hWndEdit2;
HWND hWndStatic1;
HWND hWndStatic2;
HWND hWndButton1;
HFONT hFont;
HMENU hMenu;


void clear(char[], int);
int srch(char in[], char out[]);
void do_work();
void tranSSN1(char []);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void Addmenu(HWND);
void AddControls(HWND);


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int nCmdShow){
    /*
    Function to make our entire project work. That is to fill up the values in above declared 3D and 4D matrices.
    Without this function call, program is just an empty GUI with no functionality, whatsoever.
    This function is purely written with concepts we are already aware of, but with a working/good logic.
    */

    do_work();

//------------------------------------------------------API DEFENITION *STARTS* -------------------------------->>>>

    WNDCLASSW wc={0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MywindowClass";
    wc.lpfnWndProc = WndProc;

    if (!RegisterClassW(&wc))
    {
        MessageBox(NULL, TEXT("RegisterClassW Failed!"), TEXT("Error"), MB_ICONERROR);
        return EXIT_FAILURE;
    }

    HWND hWnd;

    if (!(hWnd = CreateWindowW(L"MywindowClass", L"TranSSNator", WS_OVERLAPPEDWINDOW| WS_VISIBLE, 150, 50, 700, 700, NULL, NULL, NULL, NULL)))
    {
        MessageBox(NULL, TEXT("CreateWindow Failed!"), TEXT("Error"), MB_ICONERROR);
        return EXIT_FAILURE;
    }

    MSG msg={0};

    while (GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return EXIT_SUCCESS;


}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch (msg){
        case WM_CREATE:
            Addmenu(hWnd);
            AddControls(hWnd);
            break;

        case WM_CHAR:
            switch (wParam){
                case VK_RETURN:
                    printf("hello");
                    break;
            }

        case WM_COMMAND:
            switch (wParam){
                case 1:
                    MessageBeep(MB_OK);
                    break;

                case 2:
                    MessageBeep(MB_ICONINFORMATION);
                    break;

                case 3:
                    DestroyWindow(hWnd);
                    break;

                case 4:
                    ;
                    char in[50], fin[50], ch;
                    int i=0;
                    fin[0]='\0';

                    GetWindowTextA(hWndEdit1, in, 50);
                    tranSSN1(in);

                    FILE *fm=fopen("NEW.txt", "r");

                    while((ch=fgetc(fm))!=EOF){
                        fin[i++]=ch;
                    }

                    fin[i]='\0';
                    fclose(fm);

                    SetWindowTextA(hWndEdit2, fin);

                    break;

                default:
                    break;

            }

            break;

        case WM_DESTROY:
            PostQuitMessage(EXIT_SUCCESS);
            break;

        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
            return FALSE;
    }
}

//------------------------------------------------------API DEFENITION *ENDS* -------------------------------->>>>


//API related function to add Menus
void Addmenu(HWND hWnd){
    hMenu=CreateMenu();
    HMENU hFileMenu=CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
    AppendMenu(hFileMenu, MF_STRING, 1, "New");
    AppendMenu(hFileMenu, MF_STRING, 2, "Open");
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hFileMenu, MF_STRING, 3, "Exit");

    AppendMenu(hMenu, MF_STRING, NULL, "Help");

    SetMenu(hWnd,hMenu);

}


//API related function to add Child Windows
void AddControls(HWND hWnd){
    hWndEdit1 = CreateWindow("Edit",
                             TEXT(""),
                             WS_CHILD | ES_MULTILINE | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
                             50, 100, 400, 100,
                             hWnd, NULL, NULL, NULL);

    hFont=CreateFontA(0,12,0,0,0,0,0,0,0,0,0,0,0,TEXT("TAB-Tamil045"));
    SendMessage(hWndEdit2,WM_SETFONT,(WPARAM)hFont,0);

    hWndEdit2 = CreateWindow("Edit",
                             TEXT(""),
                             WS_CHILD | ES_MULTILINE | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
                             50, 300, 400, 100,
                             hWnd, NULL, NULL, NULL);

    hFont=CreateFontA(0,12,0,0,0,0,0,0,0,0,0,0,0,TEXT("TAB-Tamil045"));
    SendMessage(hWndEdit2,WM_SETFONT,(WPARAM)hFont,0);

    hWndStatic1 = CreateWindow("Static",
                                   TEXT("ENG CONTENT: "),
                                   WS_CHILD|WS_VISIBLE,
                                   50, 60, 100, 30,
                                   hWnd, NULL, NULL, NULL);

    hWndStatic2 = CreateWindow("Static",
                                   TEXT("TAMIL CONTENT: "),
                                   WS_CHILD|WS_VISIBLE,
                                   50, 260, 100, 30,
                                   hWnd, NULL, NULL, NULL);

    hWndButton1 = CreateWindow("Button",
                                   TEXT("Transliterate"),
                                   WS_CHILD |  BS_PUSHBUTTON| WS_VISIBLE,
                                   225, 210, 210, 75,
                                   hWnd, (HMENU) 4,  NULL, NULL);


}


//One of our driver functions. As commented in line38, this function is crucial for the program to work
void do_work(){
    int x5,y5,z5;

    //Declaring data to null, to avoid any future possible errors
    for(x5=0; x5<N2; x5++){
        for(y5=0;y5<10;y5++){
            cone[x5][y5][0]='\0';
        }

    }
    for(x5=0; x5<N2; x5++){
        for(y5=0;y5<10;y5++){
            cont[x5][y5][0]='\0';
        }
        ;
    }
    for(x5=0; x5<N1; x5++){
        for(y5=0;y5<10;y5++){
            vowt[x5][y5][0]='\0';
        }

    }
    for(x5=0; x5<N1; x5++){
        for(y5=0;y5<10;y5++){
            vowe[x5][y5][0]='\0';
        }

    }

    char ch;
    //Opening Vowels and Consonants file to read Key-Mappings
    FILE *fv=fopen("Vowels.txt", "r+");
    FILE *fc=fopen("Consonants.txt", "r+");
    int i=0;
    char temp[50];

    //Loop to read Vowels file
    while((ch=fgetc(fv))!=EOF){

        if (ch!='\n'){
            temp[i++]=ch;

        }
        else{
            temp[i++] = '\n';
            temp[i]='\0';
            int j=0;
            char tam[5];
            char eng[5];


            for(; temp[j]; j++){
                if (temp[j]!='='){
                    tam[j]=temp[j];
                }
                else{
                    int r=j-1;
                    tam[r]='\0';
                    j++;
                    j++;
                    break;
                }

            }

            strcpy(&vowt[cv][0][0],tam);

            int k=0;

            for(; temp[j]; k++){
                if(temp[j]!='\n'){
                    eng[k]=temp[j++];

                }
                else{
                    j++;
                    eng[k]='\0';
                    int w=0;

                    char e1[5];
                    int r=0;
                    int m=0;
                    for(; eng[r]; r++){
                        if(eng[r]!=','){
                            e1[m++]=eng[r];
                        }
                        else{
                            e1[m]='\0';
                            strcpy(&vowe[cv][w++][0],e1);
                            m=0;
                            clear(e1,5);
                        }

                    }

                }

            }

            clear(temp, 50);
            i=0;
            cv++;

        }

    }

    //Loop to read Consonants file
    while((ch=fgetc(fc))!=EOF){

        if (ch!='\n'){
            temp[i++]=ch;

        }
        else{
            temp[i++] = '\n';
            temp[i]='\0';
            int j=0;
            char tam[5];
            char eng[5];


            for(; temp[j]; j++){
                if (temp[j]!='='){
                    tam[j]=temp[j];
                }
                else{
                    int r=j-1;
                    tam[r]='\0';
                    j++;
                    j++;
                    break;
                }
            }

            strcpy(&cont[cc][0][0],tam);

            int k=0;

            for(; temp[j]; k++){
                if(temp[j]!='\n'){
                    eng[k]=temp[j++];

                }
                else{
                    j++;
                    eng[k]='\0';
                    int w=0;

                    char e1[5];
                    int r=0;
                    int m=0;
                    for(; eng[r]; r++){
                        if(eng[r]!=','){
                            e1[m++]=eng[r];
                        }
                        else{
                            e1[m]='\0';
                            strcpy(&cone[cc][w++][0],e1);
                            m=0;
                            clear(e1,5);
                        }

                    }

                }

            }
            clear(temp, 50);
            i=0;
            cc++;
        }
    }

    fclose(fv);
    fclose(fc);

    i=0;
    FILE *fs=fopen("UyirMei.txt", "r+");   //Filer pointer to read UyirMei ezhithikal
    int f;

    int x1=0;
    //FILLING UP OUR MATT MATRIX--------------------------->>>>
    //Making our first row of our 4D matrix with Tamil letters in the appropriate places
    for(f=1; f<N1+1; f++){
        strcpy(&matt[0][f][0][0], vowt[x1][0]);
        x1++;

    }

    x1=0;
    //Making our first column of our 4D matrix with Tamil letters in the appropriate places
    for(f=1; f<N2+1; f++){
        strcpy(&matt[f][0][0][0], cont[x1][0]);
        x1++;
    }

    int K=01;

    //Loop to read UyirMei file
    while((ch=fgetc(fs))!=EOF){

        if (ch!='\n'){
            temp[i++]=ch;

        }
        else{
            temp[i++] = ' ';
            temp[i]='\0';
            int j=0,r=0;
            int w=1;
            char tam[5];

            for(; temp[j]; j++){

                if (temp[j]!=' '){
                    tam[r++]=temp[j];
                }
                else{
                    if(K!=25){
                        tam[r]='\0';
                        strcpy(&matt[K][w++][0][0],tam);
                        clear(tam, 5);
                        r=0;
                    }
                    else{
                        break;
                    }
                }

            }

            clear(temp,50);
            i=0;
            K++;
        }

    }

    int y1=0;
    x1=0;

    //FILLING UP OUR MATE MATRIX--------------------------->>>>
    //Making our first row of our 4D matrix with English letters in the appropriate places
    for(f=1; f<N1+1; f++){
        for(y1=0; y1<10; y1++){
            strcpy(&mate[0][f][y1][0], vowe[x1][y1]);
        }
        x1++;

    }

    //Making our first Column of our 4D matrix with English letters in the appropriate places
    x1=0,y1=0;
    for(f=1; f<N2+1; f++){
        for(y1=0; y1<10; y1++){
            strcpy(&mate[f][0][y1][0], cone[x1][y1]);
        }
        x1++;
    }

    //Filling our 4D matrix with appropriate English letters at appropriate places
    int x,y,z;
    for(x=1; x<N2+1; x++){
        for(y=1; y<N1+1; y++){
            z=0;
            char temp1[50], temp2[50];
            int C;

            for(C=0; C<7; C++){
                if (cone[x-1][C][0]!='\0'){
                    strcpy(temp1,cone[x-1][C]);
                    strcpy(temp2,temp1);
                    int D;

                    for(D=0; D<3; D++){
                        if(vowe[y-1][D][0]!='\0'){
                            strcat(temp1, vowe[y-1][D]);
                            strcpy(&mate[x][y][z++][0],temp1);
                            clear(temp1, 50);
                            strcpy(temp1,temp2);
                        }
                    }

                }
                clear(temp1,50);
                clear(temp2,50);
            }
        }
    }

    /*
    int x3,y3,z3;
    for(x3=0; x3<N2+1; x3++){
        for(y3=0; y3<N1+1; y3++){
            printf("{");
            for(z3=0; z3<18; z3++){
                if(mate[x3][y3][z3][0]!='\0'){
                    printf("%s, ", mate[x3][y3][z3]);
                }
            }
            printf("}, ");
        }
        printf("\n");
    }
    */

}


/*
Our actual code that does our transliteration job.
It goes through the string, find where to break, and get the appropriate Tamil character till that break
in - input string, fin- final string, cap- captured string
*/
void tranSSN1(char in[50]){
    int i=0;
    int prev=0;
    int ic=0;
    char fin[50];
    fin[0]='\0';
    char cap[50];
    char t[50];
    int j;

    for(i=0; i<strlen(in); i++){

        for(j=prev;j<=i;j++){
            t[ic++]=in[j];
        }
        t[ic]='\0';

        if (srch(t,cap)){
            //printf("1%s ", t);
            ic=0;

        }
        else{

            if(in[i]==' '){
                strcat(fin,cap);
                strcat(fin," ");
                prev=i+1;
                clear(t,50);
                clear(cap,50);
                ic=0;
            }
            else{
                //printf("0%s ", t);
                strcat(fin,cap);
                prev=i;
                i--;
                ic=0;

            }
        }
    }
    strcat(fin,cap);
    FILE *fw=fopen("NEW.txt", "w");
    fprintf(fw,"%s",fin);
    fclose(fw);
}


/*
This is the function that takes an input string, and receives an output string. This function not only
searches for the given in string, but once the search is done, it puts the appropriate Tamil character into out string
*/
int srch(char in[], char out[]){
    int x,y,z;
    int R=0;
    for(x=0; x<N2+1; x++){
        for(y=0; y<N1+1; y++){
            for(z=0; z<18; z++){
                if(!strcmp(mate[x][y][z],in)){
                    strcpy(out,matt[x][y][0]);
                    R=1;
                    return R;
                }

            }

        }

    }

    return R;

}


//Basic clear function
void clear(char a[], int N){
    int i=0;
    for(; i<N; i++){
        a[i]=0;
    }
}

