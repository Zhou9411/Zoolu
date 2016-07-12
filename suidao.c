/*
		������� By croptree
		Last update: 2012.1.05
		F2 ����Բ��������ߵĸ߲ƫ�༰�뾶 
*/

# include "9860g.h"
#define eps (0.01)
#define zero(x) (((x)>0?(x):-(x))<eps)

struct point{
	double x;
	double y;
};

static int R_L = 1;
static double sd_x = 0.0 ;		/*  X����			*/
static double sd_y = 0.0 ;		/*  Y����			*/
static double sd_z = 0.0 ;		/*  Z����			*/
static double sd_h = 0.0 ;		/*  ����Բ�ĸ߳�ֵ����+��-��	*/
static double sd_d = 0.0 ;		/*  ����Բ��ƫ��ֵ����-��+��	*/
static double sd_r = 0.0 ;		/*  ����Բ�İ뾶ֵ				*/
static double sd_cqw = 0.0 ;	/*	��Ƿ�ڵ�ֵ��+���ڣ�-Ƿ�ڣ�	*/
static double sd_scr = 0.0 ;	/*	ʵ��뾶�������ɶ����б�߳�*/

/* 
���ȫ�ֱ��� ��x �������ߵ�ƫ�࣬y �������ߵĸ߲�) 
extern BYTE sd_flag ;
extern int SD_size;
extern double* SD_start_x ;		�������X
extern double* SD_start_y ;		�������Y
extern double* SD_end_x ;		�յ�����X
extern double* SD_end_y ;		�յ�����Y
extern double* SD_circle_x ;	Բ��X
extern double* SD_circle_y ;	Բ��Y
extern double* SD_R ;	 		�뾶

Ҫ�����л���ʱ�������д��뼴�ɣ�
sd_flag = load_SD_data(sd_flag) ;
sd_flag�Ƿ����������ݿ����
��С��SD_size��ֱ�����������ü���SD_start_x[0]
���ΪSD_start_x[SD_size-1]
*/
double FS_A(double x1, double y1, double x2, double y2,	int type);	/*	type = 0���ؽǶȣ����򷵻ػ���*/
double FS_D(double x1, double y1, double x2, double y2);
void PrintIcon (int index, char* text, int sel); 

int Suidao_DM(void)
{
	int display = 0;
	double sd_pj = 0.0 ;	/*	��������ߵľ���	*/
	double sd_gc = 0.0 ;	/*	���������ߵĸ߲�	*/
	unsigned int key = 0 ;
	unsigned int back_key ;
	BYTE exit_flag = FALSE;
	BYTE xyrow = 0 ;
	int shuaxin = TRUE;		/*	ˢ��	*/

	while (exit_flag != TRUE)  {
		
		switch(key) {
 		case KEY_CTRL_F1:	default: 
 			if (key == KEY_CTRL_F1)	shuaxin == TRUE;
			if (shuaxin){
				Bdisp_AllClr_DDVRAM() ; 
				Print_zh("������� ", 0, 1, VERT_REV) ;
				PrintIcon (0,"Home",0);
				PrintIcon (1,"Set",0);
				PrintIcon (2,"SQX",0);
				PrintIcon (3,"DM",0);
				(R_L > 0) ? PrintIcon (4,"YOU",0) : PrintIcon (4,"ZUO",1);
				PrintIcon (5,"Help",0);
				shuaxin = FALSE;
			}
			back_key = key ;
			Bdisp_AreaClr_DDVRAM(&clear_area) ;
			Print_zh("X���� ", 20, 6, 0) ;
			Print_zh("Y���� ", 20, 22, 0) ;
			Print_zh("Z���� ", 20, 38, 0) ;
			
			
			 if (xyrow > 2) {
			 		if (!sd_flag)	{
						Warning("δ������� ",2);
						//exit_flag = TRUE ;	//ǿ���˳��Խ�������������ݽ�������� fix by ��֮����
						xyrow = 0; /*	�ѽ���������TOP		*/
						key = KEY_CTRL_F4;
					break ;
				}
 				xyrow = 0 ;
 				x = sd_x ;
 				y = sd_y ;
 				SaveDisp(SAVEDISP_PAGE2) ;
 				if (InputStake(FS_NOPOPUP) == FSOK){
 					number = fs_zh ;
 					if (!GC_JS(number)) break ;
 					RestoreDisp(SAVEDISP_PAGE2) ;
				 	Bdisp_AreaClr_DDVRAM(&clear_area) ;
				 	
				 	sd_gc = sd_z -  DesignGC;
					 				 	
				 	if (!yanxin(fs_pj, sd_gc)){
				 		Warning("�������ʧ�� ",2);
				 		key == KEY_CTRL_F1; 
	 					break ;
	 				}
					Print_zh("׮��K ", 20, 0, 0) ;
					Print_zh("ƫ��D ", 20, 13, 0) ;
					Print_zh("�߲�H ", 20, 26, 0) ;
					if (sd_cqw < 0)	Print_zh("Ƿ��W ", 20, 39, 0) ;
					else			Print_zh("����T ", 20, 39, 0) ;
					Print_C(120, 4, CA = fs_zh, 3) ;
					Print_C(120, 17, CA = fs_pj, 3) ;
					Print_C(120, 30, CA = sd_gc, 3) ;
					Print_C(120, 43, CA = sd_cqw, 3) ;
					key = 0 ;
					while(key != KEY_CTRL_EXE && key != KEY_CTRL_EXIT)	GetKey(&key) ;
					key = KEY_CTRL_F1 ;
					break ;
				 }
 				RestoreDisp(SAVEDISP_PAGE2) ;
 			}
			Print_C(112, 10, CA = sd_x, 3) ;
			Print_C(112, 26, CA = sd_y, 3) ;
			Print_C(112, 42, CA = sd_z, 3) ;
			key = InputVal(59, 8+xyrow*16) ;
			switch (xyrow) {	
				case 0:   sd_x = number ? number : sd_x ; break ; 
				case 1:   sd_y = number ? number : sd_y; break ; 
				case 2:   sd_z = number ? number : sd_z; break ; 
				default:  break ;
			}
			if (key >= KEY_CTRL_F1 && key <= KEY_CTRL_F6) xyrow = 0 ;
			break ;
		case KEY_CTRL_F2:
			back_key = key ;
			Bdisp_AreaClr_DDVRAM(&clear_area) ;
			Print_zh("����H ", 20, 6, 0) ;
			Print_zh("����D ", 20, 22, 0) ;
			Print_zh("����R ", 20, 38, 0) ;
			if (xyrow > 2) { 	/* ������һ���˵�  */
				key = KEY_CTRL_F1 ; 
				xyrow = 0 ; 
				break ;
			 }
			Print_C(112, 10, CA = sd_h, 3) ;
			Print_C(112, 26, CA = sd_d, 3) ;
			Print_C(112, 42, CA = sd_r, 3) ;
			key = InputValP(59, 8+xyrow*16) ;
			switch (xyrow) {	
				case 0:   sd_h = number ? number : sd_h ; break ; 
				case 1:   sd_d = number ? number : sd_d ;break ; 
				case 2:   sd_r = number ? number : sd_r ; break ; 
				default:  break ;
			}
			if (key >= KEY_CTRL_F1 && key <= KEY_CTRL_F6) xyrow = 0 ;
			break ;

		case KEY_CTRL_F3:
			SaveDisp(SAVEDISP_PAGE2) ;

			if (sqx_flag == TRUE)	 {
				if ( InputSQstake() == TRUE) {
					if (InputSQpj() == TRUE) {	/* ����ƫ��	*/
						DesignGC = Cut_3(DesignGC) ;
						PopUpWin(3);
						locatestr(12,22) ;
						printf("�߳�:%.3f",DesignGC ) ;
						GetKey(&key);
					}
				}		
			}
			else  DebugS("δ���������� ") ;
			key =  back_key ;
			RestoreDisp(SAVEDISP_PAGE2) ;
			break ;
			
		case KEY_CTRL_F4:
			sd_flag = load_SD_data(sd_flag) ;
			key =  KEY_CTRL_F1 ;
			shuaxin = TRUE;
			break ;
			
		case KEY_CTRL_F5:
			if (R_L == -1){
				R_L = 1; 
				Warning("Ӧ�����ҷ� ",2);
			}	
			else{
				R_L = -1;
				Warning("Ӧ������� ",2);
			}
			key =  KEY_CTRL_F1 ;
			shuaxin = TRUE;
			break ;
			
			case KEY_CTRL_F6:
			Bdisp_AllClr_DDVRAM() ;
			Print_zh("Home=ˢ��ҳ�� ", 1, 2, 0) ;
			Print_zh("Set =������������ ", 1, 16, 0) ;
			Print_zh("SQX =�����߸߳� ", 1, 30, 0) ;
			Print_zh("DM  =ѡ������ļ� ", 1, 44, 0) ;
			GetKey(&key);
			Bdisp_AllClr_DDVRAM() ;
			Print_zh("ZUO =Ӧ������� ", 1, 2, 0) ;
			Print_zh("YOU =Ӧ�����ҷ� ", 1, 16, 0) ;
			Print_zh("����H=�ı�Բ�ĸ߲� ", 1, 30, 0) ;
			Print_zh("     (+���� -����)", 1, 44, 0) ;
			GetKey(&key);
			Bdisp_AllClr_DDVRAM() ;
			Print_zh("����D=�ı�Բ��ƫ�� ", 1, 2, 0) ;
			Print_zh("     (+���� -����) ", 1, 16, 0) ;
			Print_zh("����R=�ı���ư뾶 ", 1, 30, 0) ;
			Print_zh("     (+�䳤 -���)", 1, 44, 0) ;
			GetKey(&key);
			key =  KEY_CTRL_F1 ;
			shuaxin = TRUE;
			break ;

		case KEY_CTRL_UP:  
			if (xyrow > 0)  --xyrow ;  
			key = back_key ;
			break ;
		case KEY_CTRL_DOWN: 
		case KEY_CTRL_EXE:
			++xyrow ; 
			key = back_key ;
			break ;
		case KEY_CTRL_DEL:
			key = back_key ;
			break ;
		case KEY_CTRL_EXIT :
			exit_flag = TRUE ;	
			break ;
		}
	}
	return ;
}

/*	�жϴ�������ĸ�Բ�ķ�Χ��	*/
int yanxin(double cx, double cy)
{
	struct point u1;
	struct point u2;
	struct point v1;
	struct point v2;
	double A = 0.0;
	int i = 0;
	int loop = 0;
	
	cx = (R_L > 0) ? cx : cx * R_L;	/*	�ж�Ӧ������������ҷ�	*/
	do{
		u1.x = SD_start_x[i];
		u1.y = SD_start_y[i];
		u2.x = SD_end_x[i];
		u2.y = SD_end_y[i];
		v1.x = SD_circle_x[i]+sd_d;
		v1.y = SD_circle_y[i]+sd_h;
		sd_scr = FS_D(v1.x, v1.y, cx, cy);
		A = FS_A(v1.x, v1.y, cx, cy,0);
		
		/*	�����ӳ�2.929�ף��ݶ����������ж�	*/
		v2.x = cx + (2.929 + sd_scr) * (cos(A*PI/180.0));
		v2.y = cy + (2.929 + sd_scr) * (sin(A*PI/180.0));
		loop = (intersect_in(u1,u2,v1,v2));
		if (loop)	break ;
		i += 1;
		if (i >= SD_size)	return FALSE;	/*	����������ֹ	*/
	}while(!loop);
	if (SD_R[i] == 0)	return FALSE;
	if (SD_R[i] > 0)	sd_cqw = sd_scr - (SD_R[i]+sd_r);
	if (SD_R[i] < 0)	sd_cqw = fabs(cx-v1.x) - abs((SD_R[i]+sd_r));
	return TRUE;
}
/*	��������У�� eps ���ݴ�ֵ	*/
int yanzheng(void) 
{
	int i = 0;
	int j = 0;
	double r1 = 0.0;
	double r2 = 0.0;
	double Fn = 0.0;

	do{
		if (fabs(SD_R[i]) > 0.0)
		{
			r1 = FS_D(SD_start_x[i], SD_start_y[i], SD_circle_x[i], SD_circle_y[i]);
			r2 = FS_D(SD_end_x[i], SD_end_y[i], SD_circle_x[i], SD_circle_y[i]);
			if ((fabs(r1-r2) > eps || fabs(r1-fabs(SD_R[i])) > eps || fabs(r2-fabs(SD_R[i])) > eps)){
				Warning("���ݾ��Ȳ��� ",3);
				return -1;
			}
		}
			
		j = (i < SD_size-1) ? i + 1 : 0;
		if (fabs(SD_end_x[i]-SD_start_x[j]) > eps || fabs(SD_end_y[i]-SD_start_y[j]) > eps){
			Warning("�����м�϶ ",3);
			return -1;
		}
		
		i += 1;
	}while (i < SD_size);	/*	�����ƺӲ�����	*/
	Warning("����У��ͨ�� ",2);
	return 0;
}

/*	��ȡ�����ľ���	*/
double FS_D(double x1, double y1, double x2, double y2)
{
	return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

/*	��ȡ�����ķ�λ��	type = 0���ؽǶȣ�type = 1���ػ���*/
double FS_A(double x1, double y1, double x2, double y2,int type)
{
	double A = 0.0;
	A = atan((y2-y1)/(x2-x1+1.0e-8)) / PI * 180.0;
	if ((x2 - x1) < 0.0)	A += 180.0;
	if (A < 0.0)			A += 360.0;
	return A = type ? A * PI / 180 : A;
}

/*	�����Ļ�ײ��Ĳ˵�(���5���ַ�) */
void PrintIcon (int index, char* text, int sel) 
{
	index*=21;
	if (sel)
	{
		PrintMini(index+1+2*(5-strlen(text)), 59, (unsigned char*)text, 0);
		Bdisp_DrawLineVRAM(index,58,index+19,58);
		Bdisp_DrawLineVRAM(index,58,index,63);
	}
	else{
		PrintMini(index+2*(5-strlen(text)), 59, (unsigned char*)text, 0);
		Bdisp_AreaReverseVRAM(index,58,index+19,63);
	}
}

/*	���´�����Դ�� �ٶ��Ŀ� ��������Ϣδ֪��	*/
/*	���㽻��˻�(P1-P0)x(P2-P0)	*/
double xmult(struct point p1,struct point p2,struct point p0){
 return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}

/*	�е��Ƿ����߶���,�����˵�	*/
int dot_online_in(struct point p,struct point l1,struct point l2){
 return zero(xmult(p,l1,l2))&&(l1.x-p.x)*(l2.x-p.x)<eps&&(l1.y-p.y)*(l2.y-p.y)<eps;
}

/*	���������߶�ͬ��,�����߶��Ϸ���0	*/
int same_side(struct point p1,struct point p2,struct point l1,struct point l2){
 return xmult(l1,p1,l2)*xmult(l1,p2,l2)>eps;
}

/*	�����㹲��	*/
int dots_inline(struct point p1,struct point p2,struct point p3){
 return zero(xmult(p1,p2,p3));
}

/*	�����߶��ཻ,�����˵�Ͳ����غ�	*/
int intersect_in(struct point u1,struct point u2,struct point v1,struct point v2){
 if (!dots_inline(u1,u2,v1)||!dots_inline(u1,u2,v2))
 return !same_side(u1,u2,v1,v2)&&!same_side(v1,v2,u1,u2);
 return dot_online_in(u1,v1,v2)||dot_online_in(u2,v1,v2)||dot_online_in(v1,u1,u2)||dot_online_in(v2,u1,u2);
}
