// WuLasFile.h : main header file for the WULASFILE DLL
/*----------------------------------------------------------------------+
|     WuLasFile                                                         |
|       Author:     DuanYanSong  2012/11/07                             |
|            Ver 1.0                                                    |
|       Copyright (c)2012, WHU RSGIS DPGrid Group                       |
|          All rights reserved.                                         |
|     ysduan@whu.edu.cn; ysduan@sohu.com                                |
+----------------------------------------------------------------------*/
#ifndef WULASFILE_H_DUANYANSONG_2012_11_07_22_41_25112
#define WULASFILE_H_DUANYANSONG_2012_11_07_22_41_25112

#ifndef WULASFILE_LIB

#define WULASFILE_LIB  __declspec(dllimport)
#include"windef.h"

#ifdef _X64
#ifdef _DEBUG_WULASFILE
#pragma comment(lib,"WuLasFile64D.lib") 
#pragma message("Automatically linking with WuLasFile64D.lib") 
#else
#pragma comment(lib,"WuLasFile64.lib") 
#pragma message("Automatically linking with WuLasFile64.lib") 
#endif
#else
#ifdef _DEBUG_WULASFILE
#pragma comment(lib,"WuLasFileD.lib") 
#pragma message("Automatically linking with WuLasFileD.lib") 
#else
#pragma comment(lib,"WuLasFile.lib") 
#pragma message("Automatically linking with WuLasFile.lib") 
#endif
#endif

#else

#endif

#define    LAS_FILE_FLAG         "LASF"

#define    LASHDR_SIZE           227      
                
#ifndef _LASHDR
#define _LASHDR
typedef struct tagLASHDR
{
    char    strTag[4];          //4
    WORD    iFileSrcID;         //2
    WORD    iReserved;          //2
    DWORD   ulProjID1;          //4
    WORD    uiProjID2;          //2
    WORD    uiProjID3;          //2
    BYTE    ucProjID4[8];       //8
    BYTE    VerMajor;           //1
    BYTE    VerMinor;           //1
    char    SysID[32];          //32
    char    GenSoft[32];        //32    
    WORD    FileCreateDay;      //2
    WORD    FileCreateYear;     //2

    WORD    HdrSize;            //2
    DWORD   Offset2Rec;         //4
    DWORD   UserTagNum;         //4

    BYTE    recDatFmt;          //1
    WORD    recDatLen;          //2
    DWORD   recDatNum;          //4
    DWORD   recRetNum[5];       //20

    double  XScale;             //8
    double  YScale;             //8
    double  ZScale;             //8
    double  XOffset;            //8
    double  YOffset;            //8
    double  ZOffset;            //8
    double  Xmax;               //8
    double  Xmin;               //8
    double  Ymax;               //8
    double  Ymin;               //8
    double  Zmax;               //8
    double  Zmin;               //8
    
}LASHDR;
#else
#pragma message("WuLasFile.h, Warning: LASHDR alread define, be sure it was define as: struct tagLASHDR{ ;; }. \
               \nWuLasFile.h, 警告:类型 LASHDR 已经定义过,请确保其定义为: struct tagLASHDR{ ;; }.") 
#endif

#ifndef _USERTAG
#define _USERTAG
typedef struct tagUSERTAG
{
    WORD    Reserved;
    char    UserID[16];
    WORD    RecordID;
    WORD    RecordLen;
    char    Description[32];  
    
}USERTAG;
#else
#pragma message("WuLasFile.h, Warning: USERTAG alread define, be sure it was define as: struct tagUSERTAG{ ;; }. \
               \nWuLasFile.h, 警告:类型 USERTAG 已经定义过,请确保其定义为: struct tagUSERTAG{ ;; }.") 
#endif

#ifndef _RGB_WORD
#define _RGB_WORD
typedef struct tagRGB_WORD
{
    WORD  r,g,b;
}RGB_WORD;
#else
#pragma message("WuLasFile.h, Warning: RGB_WORD alread define, be sure it was define as: struct tagRGB_WORD{ WORD  r,g,b;; }. \
               \nWuLasFile.h, 警告:类型 RGB_WORD 已经定义过,请确保其定义为: struct tagRGB_WORD{ WORD  r,g,b;; }.") 
#endif



#ifndef _LASREC
#define _LASREC
#define sizeof_LASREC    20
#define sizeof_FORMT0    sizeof_LASREC
#define sizeof_FORMT1    ( sizeof_FORMT0 + sizeof(double) )
#define sizeof_FORMT2    ( sizeof_FORMT0 + sizeof(WORD)*3 )
#define sizeof_FORMT3    ( sizeof_FORMT0 + sizeof(double) + sizeof(WORD)*3 )
#define sizeof_FORMT4    ( sizeof_FORMT0 + sizeof(double) + sizeof(char)+ sizeof(LONGLONG)+sizeof(LONG)+sizeof(float)+sizeof(float)*3 )
#define sizeof_FORMT5    ( sizeof_FORMT0 + sizeof(double) + sizeof(WORD)*3 + sizeof(char)+ sizeof(LONGLONG)+sizeof(LONG)+sizeof(float)+sizeof(float)*3 )
typedef struct tagLASREC
{
    int     X,Y,Z;
        
    WORD    Intensity;    
    BYTE    LasRetFlag;
    BYTE    Classification;

    BYTE    ScanAngleRank;
    BYTE    UserData;
    WORD    PtSrcID;
    
     //double       GpsTime;
    // RGB_WORD     rgb;
}LASREC;


#define GetRetIdx(a)        (a.LasRetFlag&7)
#define GetNumOfRets(a)     ((a.LasRetFlag>>3)&7)
#define GetScanDir(a)       ((a.LasRetFlag>>6)&3)
#define IsEdgePoint(a)      (a.LasRetFlag>>7)

#define GetClassif(a)       ((a.Classification)&31)
#define IsDeleted(a)        ((a.Classification>>7)
#define IsKeyPt(a)          ((a.Classification>>6)&1)
#define IsSynthetic(a)      ((a.Classification>>5)&1)


#else
#pragma message("WuLasFile.h, Warning: LASREC alread define, be sure it was define as: struct tagLASREC{ ;; }. \
               \nWuLasFile.h, 警告:类型 LASREC 已经定义过,请确保其定义为: struct tagLASREC{ ;; }.") 
#endif

#ifndef _FPT3D_RGBA
#define _FPT3D_RGBA
typedef struct tagFPT3D_RGBA
{
    float x,y,z;
    BYTE rgba[4];    
}FPT3D_RGBA;
#else
#pragma message("WuLasFile.h, Warning: FPT3D_RGBA alread define, be sure it was define as: struct tagFPT3D_RGBA{ float x,y,z;BYTE rgba[4]; }. \
               \nWuLasFile.h, 警告:类型 FPT3D_RGBA 已经定义过,请确保其定义为: struct tagFPT3D_RGBA{ float x,y,z;BYTE rgba[4]; }.") 
#endif


#ifndef _FPT3D
#define _FPT3D
//!三维点数据定义（float型）
typedef struct tagFPT3D
{
    float x,y,z;
}FPT3D;
#else
#pragma message("WuLasFile.h, Warning: FPT3D alread define, be sure it was define as: struct tagFPT3D{ float x,y,z; }.\
               \nWuLasFile.h, 警告:类型 FPT3D 已经定义过,请确保其定义为: struct tagFPT3D{ float x,y,z; }. ") 
#endif
               
#ifndef _DPT3D
#define _DPT3D
//!三维点数据定义（double型）
typedef struct tagDPT3D
{
    double x,y,z;
}DPT3D;
#else
#pragma  message("WuLasFile.h, Warning: DPT3D alread define,be sure it was define as: struct tagDPT3D{ double x,y,z; }. \
                \nWuLasFile.h, 警告:类型 DPT3D 已经定义过,请确保其定义为: struct tagDPT3D{ double x,y,z; }") 
#endif

// 保存三维点 到 Las 文件
WULASFILE_LIB bool    Save2Las( LPCSTR lpstrLas,double *pX,double *pY,double *pZ,int ptSum );
WULASFILE_LIB bool    Save2Las( LPCSTR lpstrLas,double *pX,double *pY,double *pZ,BYTE *pRGB,int ptSum );
WULASFILE_LIB bool    Save2Las( LPCSTR lpstrLas,DPT3D *pPts,int ptSum );
WULASFILE_LIB bool    Save2Las( LPCSTR lpstrLas,FPT3D *pPts,int ptSum,double offX,double offY );
WULASFILE_LIB bool    Save2Las( LPCSTR lpstrLas,FPT3D_RGBA *pPts,int ptSum,double offX,double offY );
WULASFILE_LIB bool    Save2Las( LPCSTR lpstrLas,float *pXY,float *pZ,int ptSum,double offX,double offY );
WULASFILE_LIB bool    Append2Las( LPCSTR lpstrLas,DPT3D *pPts,int ptSum );
WULASFILE_LIB bool    Append2Las( LPCSTR lpstrLas,double gx,double gy,double gz,BYTE r,BYTE g,BYTE b );
WULASFILE_LIB bool    Append2Las( LPCSTR lpstrLas,LPCSTR lpstrLasA );

// 读取三维点 自 Las 文件
WULASFILE_LIB int     ReadSum(LPCSTR lpstrLas,BOOL bMsg);
WULASFILE_LIB bool    ReadLas(LPCSTR lpstrLas,double *pX,double *pY,double *pZ,int startPt,int ptSum);
WULASFILE_LIB bool    ReadLas(LPCSTR lpstrLas,DPT3D *pPts,int startPt,int ptSum);
WULASFILE_LIB bool    ReadLas(LPCSTR lpstrLas,FPT3D *pPts,int startPt,int ptSum,double *offX,double *offY,BOOL bMsg=TRUE );
WULASFILE_LIB bool    ReadLas(LPCSTR lpstrLas,FPT3D_RGBA *pPts,int startPt,int ptSum,double *offX,double *offY,BOOL bMsg=TRUE );

// 文件方式访问 Las 内容
#define MODE_RD   0
#define MODE_WT   1
#define MODE_RW   2
WULASFILE_LIB HANDLE   OpenLas( LPCSTR strLasFile,UINT mode,LASHDR *pLasHdr=NULL,BOOL bMsg=TRUE );  
WULASFILE_LIB BOOL     SeekLas( HANDLE hFile,UINT lasPtIdx );
WULASFILE_LIB void     CloseLas( HANDLE hFile );
WULASFILE_LIB BOOL     ReadHdr(  HANDLE hFile,LASHDR *pLasHdr );
WULASFILE_LIB BOOL     WriteHdr( HANDLE hFile,LASHDR *pLasHdr );
WULASFILE_LIB BOOL     ReadLas(  HANDLE hFile,UINT stIdx,LASREC *pLasRec,int recSize,double *gpsTm=NULL,RGB_WORD *pRgb=NULL );
WULASFILE_LIB BOOL     WriteLas( HANDLE hFile,UINT stIdx,LASREC *pLasRec,int recSize,double *gpsTm=NULL,RGB_WORD *pRgb=NULL );
WULASFILE_LIB BOOL     AppendLas( HANDLE hFile,LASREC *pLasRec,int recSize,double *gpsTm=NULL,RGB_WORD *pRgb=NULL );
WULASFILE_LIB BOOL     ReadRecs(  HANDLE hFile,UINT stIdx,BYTE* pRec,int recSum,int recSz );
WULASFILE_LIB BOOL     WriteRecs( HANDLE hFile,UINT stIdx,BYTE* pRec,int recSum,int recSz );
inline void            Rec2Grd(int iX,int iY,int iZ,double *gx,double *gy,double *gz,LASHDR& lasHdr ){
                            *gx = iX * lasHdr.XScale + lasHdr.XOffset;
                            *gy = iY * lasHdr.YScale + lasHdr.YOffset;
                            *gz = iZ * lasHdr.ZScale + lasHdr.ZOffset; 
                       };
inline void            Grd2Rec(double gx,double gy,double gz,int *iX,int *iY,int *iZ,LASHDR& lasHdr ){
                            *iX = int( (gx-lasHdr.XOffset)/lasHdr.XScale +0.5 ); 
                            *iY = int( (gy-lasHdr.YOffset)/lasHdr.YScale +0.5 );
                            *iZ = int( (gz-lasHdr.ZOffset)/lasHdr.ZScale +0.5 );
                       };

class WULASFILE_LIB CWuLasFile
{
public:
    CWuLasFile();
    virtual ~CWuLasFile();

    //! 文件访问模式
    enum OPENFLAGS{ modeRead=0x0000,modeReadWrite=0x0002,modeCreate=0x1000 };

    //!打开数据文件
    /**
    @param    lpstrPathName    LPCSTR lpstrPathName，文件名
    @param    flag            OPENFLAGS flag,打开模式 @see OPENFLAGS    
    @return    成功TRUE,失败 FALSE;
    */
    virtual BOOL        Open ( LPCSTR lpstrPathName,UINT flag=modeRead );
    //!关闭数据文件
    virtual BOOL        Close();
    
    LASHDR              GetHdr(){ return m_lasHdr; };
    void                SetHdr( LASHDR lasHdr){ if (m_nFlag!=modeRead){ m_lasHdr=lasHdr; WriteHdr(m_lasHdr); } };
    BOOL                WriteHdr( LASHDR lasHdr );

    int                 GetUserTagSum(){ return m_lasHdr.UserTagNum; }
    BOOL                ReadUserTag( int stIdx,USERTAG *pList,int listSize );

    int                 GetPtSum(){ return m_lasHdr.recDatNum; };
    BOOL                Read3DPts( int stIdx,DPT3D *pList,int listSize); 
    BOOL                Write3DPts(int stIdx,DPT3D *pList,int listSize); 
    BOOL                Read3DPts(  int stIdx,FPT3D_RGBA *pPts,int listSize,double *offX,double *offY );       
    BOOL                Write3DPts( int stIdx,FPT3D_RGBA *pPts,int listSize,double  offX,double  offY );
    BOOL                Write3DPt( int stIdx,double x,double y,double z,BYTE r,BYTE g,BYTE b );
    
    BOOL                ReadLasPt(int idx,LASREC *lasPt,double *gpsTime=NULL,RGB_WORD *pRgb=NULL);
    BOOL                ReadLasPts(int stIdx,LASREC *pList,int listSize,double *gpsTime=NULL,RGB_WORD *pRgb=NULL);
    BOOL                WriteLasPt(int idx,LASREC lasPt,double gpsTime=0,WORD r=255,WORD g=255,WORD b=255 );
    BOOL                WriteLasPts(int stIdx,LASREC *pList,int listSize,double *gpsTime=NULL,RGB_WORD *pRgb=NULL);

    BOOL                ReadRec(  int idx,BYTE* pRec,int recSz );    
    BOOL                ReadRecs( int stIdx,BYTE* pRec,int recSum,int recSz);
    BOOL                WriteRec(  int idx,BYTE* pRec,int recSz );    
    BOOL                WriteRecs( int stIdx,BYTE* pRec,int recSum,int recSz);

protected:
    HANDLE      m_hFile,m_hMap;
    LASHDR      m_lasHdr;
    UINT        m_nFlag;
    char        m_strPN[512];

public:
    enum OUTMSG{
         PROG_MSG   =   10,
         PROG_START =   11,
         PROG_STEP  =   12,
         PROG_OVER  =   13,
    };
 private:
    HWND            m_hWndRec;
    UINT            m_msgID  ;


};

#endif
