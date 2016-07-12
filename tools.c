/*
	����Compute tools
	Last update: 2010.4.20

F1 ������֪������
�ٰ�һ��F1���뵱ǰ��վ������
F2 ���뷽λ����߳�
F3 ��ʾ������ĵ�����
F4 ��������
*/


# include "9860g.h"


int Tools_Menu()
{
	unsigned int key ;
	BYTE exit_flag = FALSE ;

while (exit_flag != TRUE)  {
	Bdisp_AllClr_DDVRAM() ; 	/* clear screen */

	Print_zh("�����ߡ�", 5, 2, VERT_REV) ;	/* ��Ϊ����	By croptree		*/
	locatestr(30,2) ;	printf("F1.��·���� ") ;
	locatestr(30,16) ;	printf("F2.������� ") ;
	locatestr(30,30) ;	printf("F3.ʵ�ù��� ") ;
	locatestr(30,44) ;	printf("F4.ˮ׼���� ") ;

	GetKey(&key) ;
	switch (key) {
	case KEY_CTRL_F1:
		Kaiwa_BX();
		break ;
	case KEY_CTRL_F2:
		Suidao_DM() ;
		break ;
	case KEY_CTRL_F3:
		Usefull_Menu() ;
		break ;
	case KEY_CTRL_F4:
		Levelling() ;
		break ;
	case KEY_CHAR_5:
		break ;
	case KEY_CHAR_6:
		break ;
	case KEY_CTRL_EXIT :
		exit_flag = TRUE ;	
		break ;	
	default:
		break ;
	}
}
	return ;
}

/* ˮ׼���� */
int Levelling(void)
{
	unsigned int key,key2 ;
	unsigned int back_key ;
	BYTE exit_flag = FALSE ;
	double LevelSight = 0.0 ;
	unsigned int baseflag = 0 ;
	double frontsight = 0.0 ;
	double readchi = 0.0 ;
	double cedian  = 0.0 ;

	Bdisp_AllClr_DDVRAM() ; 	/* clear screen */
	while (exit_flag != TRUE)  {		
		DrawRect(0,0,33,127) ;
		DrawRect(0,33,30,64) ;
		DrawRect(64,33,30,63) ;
		PrintMini(112, 4, (unsigned char*)" F1", MINI_REV) ; 

		cedian  = LevelSight - readchi ;
		readchi = LevelSight - cedian ;

		locatestr(5,35) ;	printf("���� ") ;	
		locatestr(5,48) ;	printf("        ") ;
		locatestr(5,48) ;	printf("=%.3f",readchi) ;
		PrintMini(50, 37, (unsigned char*)" F2", MINI_REV) ; 
		locatestr(70,35) ;	printf("��� ") ;
		locatestr(70,48) ;	printf("        ") ;	
		locatestr(70,48) ;	printf("=%.3f",cedian) ;	
		PrintMini(112, 37, (unsigned char*)" F3", MINI_REV) ; 


		switch (key) {
		case KEY_CTRL_F1:default:
			back_key =  key ;
			locatestr(5,19) ;	printf("                 ") ;
			locatestr(5,19) ;	printf("ƽ��= %.3f[AC]",LevelSight) ;			
			
			DrawRect(1,1,31,125) ;
			ClearRect(1,34,28,62) ;
			ClearRect(65,34,28,61) ;

			if (baseflag != 2) GetKey(&key) ;
			if (key == KEY_CTRL_F1 || baseflag == 2){
				SaveDisp(SAVEDISP_PAGE2) ;		/* Save screen */
				PopUpWin(3) ;
				locatestr(18,20);
				if (baseflag ==  0) {printf("���� ") ;}
				else if (baseflag == 1) {printf("ǰ�� ") ;}
				else if (baseflag == 2 || baseflag == 9 ) {printf("���� ") ;}

				key2 = InputValP(48, 22) ;
				if (key2 == KEY_CTRL_EXE) {
					RestoreDisp(SAVEDISP_PAGE2) ;
					if (number){	
						switch (baseflag)
						{
						default: case 0:
							baseflag = 9;
							LevelSight = LevelSight + number ;	
							Printsmall(number,TRUE) ;
							break ;
						case 9:
							baseflag = 1;
							LevelSight = LevelSight + number ;	
							Printsmall(number,FALSE) ;	
							break ;
						case 1:
							baseflag = 2;
							frontsight = -number ;						
							break ;
						case 2:				
							baseflag= 1 ;
							LevelSight = LevelSight + frontsight + number ;
							Printsmall(frontsight,FALSE) ;	
							Printsmall(number,FALSE) ;	
							break ;
						}					
					}
				} else if (baseflag == 2) {
					RestoreDisp(SAVEDISP_PAGE2) ;
					if (DebugS("ȡ��תվ?\nF1-��  F6-�� ") == TRUE)  {
						baseflag = 1;
						frontsight = 0.0 ;
					}
				} else RestoreDisp(SAVEDISP_PAGE2) ;		
				
			}
			break ;
		case KEY_CTRL_F2:
			DrawRect(1,34,28,62) ;
			ClearRect(1,1,31,125) ;
			ClearRect(65,34,28,61) ;
			GetKey(&key) ;
			if (key == KEY_CTRL_F2 ){
				SaveDisp(SAVEDISP_PAGE2) ;		/* Save screen */
				PopUpWin(3) ;
				locatestr(18,20);printf("���� ") ;
				key2 = InputValP(48, 22) ;
				readchi = number ? number : readchi ;
				cedian  = LevelSight - readchi ;
				RestoreDisp(SAVEDISP_PAGE2) ;
			}
			break ;
		case KEY_CTRL_F3:
			DrawRect(65,34,28,61) ;
			ClearRect(1,1,31,125) ;
			ClearRect(1,34,28,62) ;
			GetKey(&key) ;
			if (key == KEY_CTRL_F3 ){
				SaveDisp(SAVEDISP_PAGE2) ;		/* Save screen */
				PopUpWin(3) ;
				locatestr(18,20);printf("��� ") ;
				key2 = InputValP(48, 22) ;
				cedian = number ? number : cedian ;
				readchi = LevelSight - cedian ;
				RestoreDisp(SAVEDISP_PAGE2) ;
			}
			break ;
		case KEY_CTRL_AC:
			baseflag = 0 ;LevelSight = 0.0 ;
			PrintMini(5,2,(const unsigned char*)"                                                 ",MINI_OVER);
			PrintMini(5,2+6,(const unsigned char*)"                                                 ",MINI_OVER);
			PrintMini(5,2+6*2,(const unsigned char*)"                                                 ",MINI_OVER);
			key = back_key ;
			break ;
		case KEY_CTRL_EXIT :
			if (DebugS("�˳�?\nF1-��  F6-�� ") == TRUE)  exit_flag = TRUE ;	
			else key = back_key ;
			break ;	
		}
	}
	return ;	
}

int Usefull_Menu(void)
{
	unsigned int key ;
	BYTE exit_flag = FALSE ;


while (exit_flag != TRUE)  {
	Bdisp_AllClr_DDVRAM() ; 	/* clear screen */

	Print_zh("��ʵ�á�", 5, 2, VERT_REV) ;	/* ��Ϊ����	By croptree		*/
	locatestr(30,2) ;	printf("F1.�������� ") ;
	locatestr(30,16) ;	printf("F2.���귴�� ") ;
	locatestr(30,30) ;	printf("F3.�Ƕ�ת�� ") ;
	locatestr(30,44) ;	printf("F4.����λ�� ") ;

	GetKey(&key) ;
	switch (key) {
	case KEY_CTRL_F1:
		Zuobiao_ZS() ;
		break ;
	case KEY_CTRL_F2:
		Zuobiao_FS() ;
		break ;
	case KEY_CTRL_F3:
		Angel_convert() ;	
		break ;
	case KEY_CTRL_F4:
		break ;
	case KEY_CTRL_EXIT :
		exit_flag = TRUE ;	
		break ;	
	default:
		break ;
	}
}
	return ;	
}



/*  �����߰뾶�������̣����̣߳��յ���̣��յ�߳�  */
/*static	double SQ_r = 0 ;		
static	double SQ_bmile = 0 ;
static double SQ_bgc = 0 ;
static double SQ_emile = 100 ;
static	double SQ_egc = 0 ;*/

static double T = 0 ;
static double E = 0 ;
static double i1 = 0 ;
//static double DesignGC = 0 ;

static double Pobi1 = 1.0 ;		/*  �±�1  */
static double Pobi2 = 1.5 ;		/*  �±�2  */
static double TJ_G = 100 ;		/*  ̨�׸�  */
static double TJ_Width = 0 ;		/*  ̨�׿�  */
static double Add_Width = 0 ;	/*  �ӿ�ֵ  */

static double HP = -1.5 ;	//����
static double jianqu = 0.0 ;	//��Ƹ߼�ȥֵ
static double xuqiu = 0.0 ;	//����߶�
static double bianju = 0.0 ;	/*  �߾�  */

double fs_zh = 0.0 ;
double fs_pj = 0.0 ;

#define WAFANG 1
#define TIANFANG 2

int LFHP_auto(double stake, double offset) 
{
	unsigned int result_LF ;

	if (LF_flag == TRUE) {
		result_LF = LF_JS(stake) ;
		if (offset < 0){
			HP = LF_L_HP[result_LF] ;
			bianju = LF_L_Width[result_LF] ;
		}
		else {
			HP = LF_R_HP[result_LF] ;
			bianju = LF_R_Width[result_LF] ;
		}
	}
	return ;
}

int Kaiwa_BX(void)
{
	double final_a = 0.0 ;
	double S = 0.0 ;	/*  ����߳�  */
	double a = 0.0 ;	/*  ���㷽λ��  */
	double h = 0.0 ;	/*  �߲�  */

	unsigned int key = 0 ;
	unsigned int back_key ;
	unsigned int any_key ;
	BYTE exit_flag = FALSE ;
	BYTE xyrow = 0 ;
	BOOL waiyi_val = FALSE ; /* ����ֵ */
	double L_Mile =0.0 ;	/*  ���  */
	
	double GC = 0.0 ;		/*  ʵ��  */
	double AC4 = 0.0 ;		/*  �˱��������ϰֵı��������  */
	double bianxian = 0.0 ;	/* ���� */

	BYTE wt_flag = 0 ;
	BYTE crossline = FALSE ;
	double Pobi = 0.0 ;	
	unsigned int TJ_count = 0 ;	
	unsigned int temp_count = 0 ;	


	Bdisp_AllClr_DDVRAM() ; 	/* clear screen */	
	Print_zh("�����", 5, 0, VERT_REV) ;
	/* Menu F1, F2, F3:... */
	PrintMini(5, 58, (unsigned char*)" SET1", MINI_REV) ; 
	PrintMini(28, 58, (unsigned char*)" SET2 ", MINI_REV) ; 
	PrintMini(55, 58, (unsigned char*)" XQ", MINI_REV) ; 
	PrintMini(72, 58, (unsigned char*)" ZH ", MINI_REV) ; 
	PrintMini(91, 58, (unsigned char*)" GO ", MINI_REV) ; 

	PrintMini(110, 58, (unsigned char*)" D ", MINI_REV) ; 

	while (exit_flag != TRUE)  {
		switch(key) {
		case KEY_CTRL_F1: default: 
			back_key = key ;
			Bdisp_AreaClr_DDVRAM(&clear_area) ;
			
			Print_zh("��� ", 24, 6, 0) ;
			Print_zh("�±�-", 24, 22, 0) ;
			Print_zh("�±�+ ", 24, 38, 0) ;

			if (xyrow > 2) { 	/* �ж��Ƿ������һ���˵� */
				key = KEY_CTRL_F2 ; 
				xyrow = 0 ; 
				break ;
			 }
			Print_C(112, 10, CA = bianju, 3) ;
			Print_C(112, 26, CA = Pobi1, 3) ;
			Print_C(112, 42, CA = Pobi2, 3) ;
			key = InputVal(59, 8+xyrow*16) ;
			switch (xyrow) {	
			case 0:   bianju = (number > 0) ? number : bianju ; break ; 
			case 1:   Pobi1 = (number > 0) ? number : Pobi1 ;  break ; 
			case 2:   Pobi2 = (number > 0)  ? number : Pobi2 ; break ; 
			default:  break ;
			}
			if (key == KEY_CTRL_F6 || key == KEY_CTRL_F2 || key == KEY_CTRL_F3 || key == KEY_CTRL_F5) xyrow = 0 ;
			break ;

			
		case KEY_CTRL_F2:
			back_key = key ;
			Bdisp_AreaClr_DDVRAM(&clear_area) ;
			
			Print_zh("����%", 24, 6, 0) ;
			Print_zh("�׸�", 24, 22, 0) ;
			Print_zh("̨�� ", 24, 38, 0) ;
			if (xyrow > 2) { 	/* �ж��Ƿ������һ���˵� */
				key = KEY_CTRL_F3 ; 
				xyrow = 0 ; 
				break ;
			 }
			Print_C(112, 10, CA = HP, 3) ;
			Print_C(112, 26, CA = TJ_G, 3) ;
			Print_C(112, 42, CA = TJ_Width, 3) ;
			key = InputValP(59, 8+xyrow*16) ;
			switch (xyrow) {	
			case 0:   HP = number ? number : HP ; break ; 
			case 1:   TJ_G = (number > 0) ? number : TJ_G ;break ; 
			case 2:   TJ_Width = (number > 0) ? number : TJ_Width ; break ; 
			default:  break ;
			}

			if (key == KEY_CTRL_F6 || key == KEY_CTRL_F1 || key == KEY_CTRL_F3 || key == KEY_CTRL_F5) xyrow = 0 ;
			break ;

			
		case KEY_CTRL_F3:
			back_key = key ;
			Bdisp_AreaClr_DDVRAM(&clear_area) ;
			//once = FALSE ;
		
			Print_zh("��� ", 24, 6, 0) ;
			Print_zh("��ȥ ", 24, 22, 0) ;
			Print_zh("�߹� ", 24, 38, 0) ;
				  

			if (xyrow > 2) { 	/* �ж��Ƿ������һ���˵� */
				key = KEY_CTRL_F5 ; 
				xyrow = 0 ; 
				break ;
			 }
			Print_C(112, 10, CA = DesignGC, 3) ;
			Print_C(112, 26, CA = jianqu, 3) ;
			Print_C(112, 42, CA = Add_Width, 3) ;

			key = InputValP(59, 8+xyrow*16) ;

			switch (xyrow) {
			case 0:   
				DesignGC = number ? number : DesignGC ;
				break ; 
			case 1:
				jianqu = number ? number : jianqu ;
				break ;
			case 2:
				Add_Width = number ? number : Add_Width ;
				break ;
			default:  break ;
			}
			if  (key == KEY_CTRL_F6 || key == KEY_CTRL_F5 || key == KEY_CTRL_F1 || key == KEY_CTRL_F2 ) xyrow = 0 ;
			xuqiu = DesignGC - jianqu ;
			
			break ;
		case KEY_CTRL_F4:
			SaveDisp(SAVEDISP_PAGE2) ;		/* Save screen */

			if (sqx_flag == TRUE)	 {
				if ( InputSQstake() == TRUE) {
					if (InputSQpj() == TRUE) {	// ����ƫ��
						DesignGC = Cut_3(DesignGC) ;
						xuqiu = DesignGC - jianqu ;  
					}
				}		
			}
			else  DebugS("δ���������� ") ;
			key =  back_key ;
			RestoreDisp(SAVEDISP_PAGE2) ;
			break ;
		case KEY_CTRL_F5:
			back_key = key ;
			Bdisp_AreaClr_DDVRAM(&clear_area) ;
			
			Print_zh("���� ", 24, 6, 0) ;
			Print_zh("���� ", 24, 22, 0) ;
			Print_zh("ʵ�� ", 24, 38, 0) ;
			
			if (xyrow > 0) { 	/* �ж��Ƿ������һ���˵� */
				SaveDisp(SAVEDISP_PAGE3) ;	
				PopUpWin(3) ;
				if ( (xuqiu - GC) <= 0 ){
					Print_zh("�ڷ� ", 25, 20, 0) ;
					if (wt_flag == TIANFANG) crossline = TRUE ;
					wt_flag = WAFANG ;
					Pobi = Pobi1 ;
				}
				else {
					Print_zh("� ", 25, 20, 0) ;
					if (wt_flag == WAFANG) crossline = TRUE ;
					wt_flag = TIANFANG ;
					Pobi = Pobi2 ;
				}
				Print_Float(63, 24, xuqiu - GC) ;
				PrintMini(96, 36, (unsigned char*)" EXE ", MINI_REV) ; 
				GetKey(&any_key) ;
				RestoreDisp(SAVEDISP_PAGE3) ;
				
				//���������
				if (crossline == TRUE)	Warning("����任 ", 1) ;
				crossline = FALSE ;
				

				if (fabs(GC - xuqiu) > TJ_G && TJ_G != 0) {
					SaveDisp(SAVEDISP_PAGE2) ;		/* Save screen */
					bianxian = 0 ;

					TJ_count = (int)floor(fabs(GC - xuqiu) / TJ_G) ;
					if (fmod(fabs(GC - xuqiu),TJ_G) == 0)	/*�ܱ��׸��������ȥһ��*/
						TJ_count = TJ_count - 1 ;
					bianxian =bianxian + TJ_Width + TJ_G * Pobi ;
					for ( temp_count = 2 ; temp_count <= TJ_count + 1 ; ++temp_count ){
						 PopUpWin(3) ;
						 locatestr(15,20) ;
						 printf("%d�±�", temp_count) ;
						 Print_Float(73, 24, Pobi) ;
						 if (InputValP(48, 22) == KEY_CTRL_EXE) 
							Pobi = (number > 0) ? number : Pobi ;
						if (temp_count == TJ_count + 1)
							bianxian = bianxian + (fabs(GC - DesignGC) - TJ_count * TJ_G) * Pobi ;
						else
							bianxian =bianxian + TJ_Width + TJ_G * Pobi ;
					}
					bianxian = bianju + bianxian;
					RestoreDisp(SAVEDISP_PAGE2) ;
				}
				else  	bianxian = bianju + fabs(GC - DesignGC) * Pobi ;

				if (wt_flag == WAFANG) bianxian += Add_Width ;

				if (waiyi_val == TRUE) {
					waiyi_val = FALSE ;
					if ( bianxian > fabs(fs_pj) ) DebugS("����%.3fm��\n������%.3fm ",bianxian - fabs(fs_pj),bianxian) ;
					else DebugS("����%.3fm��\n������%.3fm ", bianxian - fabs(fs_pj),bianxian) ;
				}
				key = KEY_CTRL_F5 ; 
				xyrow = 0 ; 
				break ;
			 }

			if (fabs(GC - xuqiu) > TJ_G && TJ_G != 0) {
				locatestr(25,2); 
				printfMINI("=%.3f+%d Tj+%d Po",bianju+Add_Width,TJ_count,TJ_count+1) ;
			} else {	
				locatestr(54,2); 
				if (wt_flag == WAFANG) printfMINI("=%.1f+%.1f+%.3f*%.1f",bianju,Add_Width,fabs(GC-DesignGC),Pobi) ;
				else printfMINI("=%.1f+%.3f*%.1f",bianju,fabs(GC-DesignGC),Pobi) ;
			}
	
			Print_C(112, 11, CA = bianxian, 3) ;
			Print_C(112, 26, CA = xuqiu, 3) ;
			Print_C(112, 42, CA = GC, 3) ;
			key = InputValP(59, 40+xyrow*16) ;
			switch (xyrow) {
			case 0:   
				GC = number ? number : GC ; 
				break ; 
			default:  break ;
			}
			
			break ;			
		case KEY_CTRL_F6:
			back_key = key ;
			Bdisp_AreaClr_DDVRAM(&clear_area) ;
			SaveDisp(SAVEDISP_PAGE2) ;		/* Save screen */
			if ((qxys_flag == TRUE  || xyf_flag == TRUE) && sqx_flag == TRUE)	 {
			Print_zh("�Ƕ� ", 24, 6, 0) ;	
			Print_zh("���� ", 24, 21, 0) ;
			Print_zh("�߲� ", 24, 35, 0) ;
			if (xyrow > 2) { 	/* �ж��Ƿ������һ���˵� */
				if (a > 360.0) {Warning("�Ƕȹ��� ", 2) ; key = KEY_CTRL_F6 ; }
				else {
					xyrow = 0 ; 
					key = KEY_CTRL_F5 ; 

					final_a = (25 * a - 6 *(int)a - 10 * Cut_2(a)) / 9 * PI / 180 + total_set.azimuth ;
					x = Cut_3(total_set.stat_point.x + S * cos(final_a)) ;
					y = Cut_3(total_set.stat_point.y + S * sin(final_a)) ;
					if (InputStake(KEY_CTRL_F4) == FSOK){
						if (sqx_flag == TRUE) {
							number = fs_zh ;
							GC_JS(number) ;
							//·�����¸��� 
							LFHP_auto(fs_zh, fs_pj) ;

							if (fabs(fs_pj) <= bianju)
								DesignGC = DesignGC + fabs(fs_pj) * HP / 100 ;
							else 
								DesignGC = DesignGC + bianju * HP / 100 ;	
							DesignGC = Cut_3(DesignGC) ;
							xuqiu = DesignGC - jianqu ;  

							GC = total_set.stat_point.z + total_set.station_ht + h - total_set.prism_ht ;
							if (fabs(fs_pj) < bianju){		//С�ڰ���߾����ƶ����߾� 
								DebugS("����%.3fm��\n���%.3fm�߾� ",bianju-fabs(fs_pj), bianju) ;
							}
							else {
								waiyi_val = TRUE ;
							}
						} else {
							GC = total_set.stat_point.z + total_set.station_ht + h - total_set.prism_ht ;
						}
					}
					else key = KEY_CTRL_F6 ; 
					RestoreDisp(SAVEDISP_PAGE2) ;
				}
				break ;
			 }
			Print_CC_Val(108, 11, CB = a) ;
			Print_C_Val(CA = S, CB = h) ;
			
			key = InputVal(55, 8+xyrow*14) ;
			if (number < 100000){
			switch (xyrow) {
			case 0:   a = (number > 0 && number <= 360) ? number : a ; break ; 
			case 1:   S = (number > 0) ? number : S ; break ; 
			case 2:   h = number ? number : h ;  ; break ;
			default:  break ;
			}
			}
			}else {
				Warning("δ�������� ",2) ;
				RestoreDisp(SAVEDISP_PAGE2) ;
				key = KEY_CTRL_F5 ;
			}
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

static double SQ_dist = 0.0 ;

int InputSQpj(void)
{
	unsigned int key ;
	BYTE exit_flag = FALSE ;
	double stake= 0.0 ;

	stake = number ;		//����InputSQstake�������׮�� 

	PopUpWin(3) ;
	Print_zh("ƫ�� ", 18, 20, 0) ;
	while (exit_flag != TRUE) {
		Print_Float(65, 24, SQ_dist) ;
		key = InputValP(48, 22) ;
		switch (key){
		case KEY_CTRL_EXE:
			SQ_dist = number ? number : SQ_dist ;
			LFHP_auto(stake, SQ_dist) ;	//·�����¸��� 

			if (SQ_dist == 0 ) { exit_flag = TRUE ; break ;}	

			if (fabs(SQ_dist) <= bianju)
				DesignGC = DesignGC + fabs(SQ_dist) * HP / 100 ;
			else 
				DesignGC = DesignGC + bianju * HP / 100 ;		
			exit_flag = TRUE ;
			break ;
		case KEY_CTRL_EXIT:
			exit_flag = TRUE ;
			break ;
		default:
			break ;
		}
	}
	return TRUE ;
}

int Zuobiao_ZS(void)
{
	unsigned int key = 0 ;
	unsigned int back_key ;
	BYTE exit_flag = FALSE ;
	BYTE xyrow = 0 ;
	double x = 0.0 ;
	double y = 0.0 ;
	double S = 0.0 ;	/*  �߳�  */
	double a = 0.0 ;	/*  ��λ��  */
	S_POINT final_p = {0.0, 0.0, 0.0} ;
	double final_a = 0.0 ;
	
	Bdisp_AllClr_DDVRAM() ; 	/* clear screen */	
	Print_zh("�����㡡", 5, 0, VERT_REV) ;
	/* Menu F1, F2, F3:... */
	PrintMini(5, 58, (unsigned char*)" XY ", MINI_REV) ; 
	PrintMini(24, 58, (unsigned char*)" SA ", MINI_REV) ; 
	PrintMini(42, 58, (unsigned char*)" GO ", MINI_REV) ; 
	PrintMini(60, 58, (unsigned char*)" Save ", MINI_REV) ; 
	
	PrintMini(110, 58, (unsigned char*)" ? ", MINI_REV) ; 
	
	while (exit_flag != TRUE)  {
		switch(key) {
		case KEY_CTRL_F1: default: 
			back_key = key ;
			Bdisp_AreaClr_DDVRAM(&clear_area) ;
			
			Print_zh("��֪�� ", 22, 6, 0) ;
			PrintXY(25, 25, (unsigned char*)"X :", 0) ;
			PrintXY(25, 39, (unsigned char*)"Y :", 0) ;

			if (xyrow > 1) { 	/* �ж��Ƿ������һ���˵� */
				key = KEY_CTRL_F2 ; 
				xyrow = 0 ; 
				break ;
			 }
			Print_C_Val(CA = x, CB = y) ;
			key = InputVal(50, 22+xyrow*14) ;
			if (key == KEY_CTRL_F1) {
				x = total_set.stat_point.x ;
				y = total_set.stat_point.y ;
			}
			if (number < 100000) {
				switch (xyrow) {
				case 0:   x = number ? number : x ; break ; 
				case 1:   y = number ? number : y ; break ; 
				default:  break ;
				}
			}
			break ;
		case KEY_CTRL_F2:
			back_key = key ;
			Bdisp_AreaClr_DDVRAM(&clear_area) ;
			
			Print_zh("���� ", 22, 6, 0) ;	
			Print_zh("�н� ", 24, 22, 0) ;
			Print_zh("�߳� ", 24, 35, 0) ;
			if (xyrow > 1) { 	/* �ж��Ƿ������һ���˵� */
				key = KEY_CTRL_F3 ; 
				xyrow = 0 ; 
				break ;
			 }
			Print_C_Val(CA = a, CB = S) ;
			Print_CC_Val(108, 24, CB = a) ;
			key = InputVal(55, 22+xyrow*14) ;
			if (number < 100000){
			switch (xyrow) {
			case 0:   a = number ? number : a ; break ; 
			case 1:   S = number ? number : S ; break ; 
			default:  break ;
			}
			}
			break ;
		case KEY_CTRL_F3:
			/* ������� */
			if (x == 0.0 || y == 0.0 || S == 0.0 || a == 0.0 ) { 
				xyrow = 0 ;
				Warning("���ݲ���ȫ ", 2) ;
				key = back_key ;
				break ;
			} else if (a > 360.0) {
				xyrow = 1 ;
				Warning("�н�ֵ��Ч ", 2) ;
				key = back_key ;
				break ;
			}
			back_key = key ;
			Bdisp_AreaClr_DDVRAM(&clear_area) ;
			
			Print_zh("����� ", 22, 6, 0) ;
			PrintXY(25, 25, (unsigned char*)"X :", 0) ;
			PrintXY(25, 39, (unsigned char*)"Y :", 0) ;
			
			final_a = (25 * a - 6 *(int)a - 10 * Cut_2(a)) / 9 * PI / 180 + total_set.azimuth ;
			final_p.x = x + S * cos(final_a) ;
			final_p.y = y+ S * sin(final_a) ;
			Print_C_Val(CA = final_p.x , CB = final_p.y) ;
			GetKey(&key) ;
			break ;
		case KEY_CTRL_F4:
			SavePoint(final_p) ;
			key = back_key ;
			break ;
		case KEY_CTRL_F5:
			key = back_key ;
			break ;	
		case KEY_CTRL_F6:
			back_key = key ;
			Bdisp_AreaClr_DDVRAM(&clear_area) ;
			
			Print_zh("ʹ��˵�� ", 22, 6, 0) ;
			GetKey(&key) ;
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

int Zuobiao_FS(void)
{
	unsigned int key = 0 ;
	unsigned int back_key ;
	BYTE exit_flag = FALSE ;
	BYTE xyrow = 0 ;
	double x1 = 0.0 ;
	double y1 = 0.0 ;
	double x2 = 0.0 ;
	double y2 = 0.0 ;
	double S = 0.0 ;	/*  �߳�  */
	double a = 0.0 ;	/*  ��λ��  */
	S_POINT final_p = {0.0, 0.0, 0.0} ;
	double final_a = 0.0 ;
	
	Bdisp_AllClr_DDVRAM() ; 	/* clear screen */	
	Print_zh("�����㡡", 5, 0, VERT_REV) ;
	/* Menu F1, F2, F3:... */
	PrintMini(5, 58, (unsigned char*)" XY1 ", MINI_REV) ; 
	PrintMini(27, 58, (unsigned char*)" XY2 ", MINI_REV) ; 
	PrintMini(50, 58, (unsigned char*)" GO ", MINI_REV) ; 
	
	PrintMini(110, 58, (unsigned char*)" ? ", MINI_REV) ; 
	
	while (exit_flag != TRUE)  {
		switch(key) {
		case KEY_CTRL_F1: default: 
			back_key = key ;
			Bdisp_AreaClr_DDVRAM(&clear_area) ;
			
			Print_zh("��֪��1 ", 22, 6, 0) ;
			PrintXY(25, 25, (unsigned char*)"X1:", 0) ;
			PrintXY(25, 39, (unsigned char*)"Y1:", 0) ;

			if (xyrow > 1) { 	/* �ж��Ƿ������һ���˵� */
				key = KEY_CTRL_F2 ; 
				xyrow = 0 ; 
				break ;
			 }
			Print_C_Val(CA = x1, CB = y1) ;
			key = InputVal(50, 22+xyrow*14) ;
			if (key == KEY_CTRL_F1) {
				x1 = total_set.stat_point.x ;
				y1 = total_set.stat_point.y ;
			}
			switch (xyrow) {
			case 0:   x1 = number ? number : x1 ; break ; 
			case 1:   y1 = number ? number : y1 ; break ; 
			default:  break ;
			}
			break ;
		case KEY_CTRL_F2:
			back_key = key ;
			Bdisp_AreaClr_DDVRAM(&clear_area) ;
			
			Print_zh("��֪��2 ", 22, 6, 0) ;
			PrintXY(25, 25, (unsigned char*)"X2:", 0) ;
			PrintXY(25, 39, (unsigned char*)"Y2:", 0) ;

			if (xyrow > 1) { 	/* �ж��Ƿ������һ���˵� */
				key = KEY_CTRL_F3 ; 
				xyrow = 0 ; 
				break ;
			 }
			Print_C_Val(CA = x2, CB = y2) ;
			key = InputVal(50, 22+xyrow*14) ;
			if (key == KEY_CTRL_F2) {
				x2 = total_set.bak_point.x ;
				y2 = total_set.bak_point.y ;
			}
			switch (xyrow) {
			case 0:   x2 = number ? number : x2 ; break ; 
			case 1:   y2 = number ? number : y2 ; break ; 
			default:  break ;
			}
			break ;
		case KEY_CTRL_F3:
			/* ������� */
			if (x1 == 0.0 || y1 == 0.0 || x2 == 0.0 || y2 == 0.0 ) { 
				xyrow = 0 ;
				Warning("���ݲ���ȫ ", 2) ;
				key = back_key ;
				break ;
			}
			back_key = key ;
			Bdisp_AreaClr_DDVRAM(&clear_area) ;
			
			Print_zh("����ֵ ", 22, 6, 0) ;
			Print_zh("�н� ", 24, 22, 0) ;
			Print_zh("�߳� ", 24, 35, 0) ;
			
			a = atan2((y2 - y1), (x2 - x1)) ;
			S = (y2 - y1) / sin(a) ;
			angel = a ;// - total_set.azimuth ;
			Print_Angel(59, 24) ;
			Print_Float(59, 38, S) ;
			
			GetKey(&key) ;

			break ;
		case KEY_CTRL_F4:  case KEY_CTRL_F5:
			key = back_key ;
			break ;
		case KEY_CTRL_F6:
			back_key = key ;
			Bdisp_AreaClr_DDVRAM(&clear_area) ;
			
			Print_zh("ʹ��˵�� ", 22, 6, 0) ;
			GetKey(&key) ;
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

int Angel_convert(void)
{
	unsigned int key = KEY_CTRL_F1 ;
	unsigned int back_key ;
	BYTE exit_flag = FALSE ;
	double convert_num = 0 ;
	
	Bdisp_AllClr_DDVRAM() ; 	/* clear screen */	
	Print_zh("��ת����", 5, 0, VERT_REV) ;
	/* Menu F1, F2, F3:... */
	PrintMini(5, 58, (unsigned char*)" F1 60=>10 ", MINI_REV) ; 
	PrintMini(52, 58, (unsigned char*)" F2 10=>60 ", MINI_REV) ; 
	
	PrintMini(110, 58, (unsigned char*)" ? ", MINI_REV) ; 
	
	while (exit_flag != TRUE)  {
		switch(key) {
		case KEY_CTRL_F1: 
			back_key = key ;
			Print_zh("60���ƽǶ� ", 25, 10, 0) ;
			PrintMini(94, 33, (unsigned char*)" EXE ", MINI_REV) ; 
			PrintXY(27,32, (unsigned char *)"          ", 0) ;
			Print_C(83,32,CB=convert_num,5) ;
			key = InputValP(25, 30) ;
			convert_num = number ? number : convert_num ;

			break ;
		case KEY_CTRL_F2:
			back_key = key ;
			Print_zh("10���ƽǶ� ", 25, 10, 0) ;
			PrintMini(94, 33, (unsigned char*)" EXE ", MINI_REV) ; 
			Print_C(83,32,CB=convert_num,5) ;
			key = InputValP(25, 30) ;
			convert_num = number ? number : convert_num ;
			break ;
		case KEY_CTRL_F6:
			SaveDisp(SAVEDISP_PAGE2) ;		/* Save screen */
			Bdisp_AreaClr_DDVRAM(&clear_area) ;
			
			Print_zh("F1 ��ʮ���ƽǶ�\nתʮ����\nF2 ʮ���ƽǶ�\nת��ʮ���� ", 22, 1, 0) ;
			GetKey(&key) ;
			key = back_key ;
			RestoreDisp(SAVEDISP_PAGE2) ;
			Bdisp_PutDisp_DD() ;
			break ;
		case KEY_CTRL_EXE:
			if (back_key == KEY_CTRL_F1) {
				locatestr(28,42) ;
				printf("%.5f",Sixty2ten(convert_num)) ;
			}
			else if (back_key == KEY_CTRL_F2) {
				locatestr(28,42) ;
				printf("%.4f  ",Ten2sixty(convert_num)) ;
			}	
			key = back_key ;
			break ;
		case KEY_CTRL_DEL:
			key = back_key ;
			break ;
		case KEY_CTRL_EXIT :
			exit_flag = TRUE ;
			break ;
		default: 
			key = back_key ;
			break ;
		}
	}
	return ;
}
