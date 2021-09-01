// WuDPGImage.h : main header file for the WUDPGIMAGE DLL
/*----------------------------------------------------------------------+
|		WuDPGImage														|
|       Author:     DuanYanSong  2011/04/28   							|
|            Ver 1.0													|
|       Copyright (c)2011, WHU RSGIS DPGrid Group						|
|	         All rights reserved.                                       |
|		ysduan@sohu.com; ysduan@whu.edu.cn								|
+----------------------------------------------------------------------*/
#ifndef WUDPGIMAGE_H_DUANYANSONG_2011_04_28_09_40_42968
#define WUDPGIMAGE_H_DUANYANSONG_2011_04_28_09_40_42968

#ifndef WUDPGIMAGE_LIB

#define WUDPGIMAGE_LIB  __declspec(dllimport)
#ifdef _DEBUG_WUDPGIMAGE
#pragma comment(lib,"WuDPGImageD.lib") 
#pragma message("Automatically linking with WuDPGImageD.lib") 
#else
#pragma comment(lib,"WuDPGImage.lib") 
#pragma message("Automatically linking with WuDPGImage.lib") 
#endif

#else

#ifdef _DEBUG
#define _DEBUG_SPVZIMAGE
#endif

#endif

#include "SpVZImage.h"
#ifndef _STDPGIMAGE

#else
#define CWuDPGImage CStDPGImage
#ifndef CWuDPGImage
#pragma message("error (1). Not define CStDPGImage") 
#endif

#endif


enum EXT_TYPE{
    EXT_NONE		=  0,
    ET_GEOINF		=  1, // 设置地理信息
	ET_GEOINF_PROJ	=  2, // 设置地理+投影信息
};

#define MAX_GTIF_PROJPARMS 	8
#ifndef _GEO_PROJPAR
#define _GEO_PROJPAR
typedef struct tagGEO_PROJPAR{
	double  mtrx[6];

	short	Model; // From GTModelTypeGeoKey tag.  Can have the values ModelTypeGeographic or ModelTypeProjected.
	short	PCS;   // From ProjectedCSTypeGeoKey tag.  For example PCS_NAD27_UTM_zone_3N
	
	short	GCS;   // From GeographicTypeGeoKey tag.  For example GCS_WGS_84 or GCS_Voirol_1875_Paris.  Includes datum and prime meridian value.
	short	PM;    // Prime meridian from GeogPrimeMeridianGeoKey.  For example PM_Greenwich or PM_Paris.      
	short	Ellipsoid;  // Ellipsoid identifier from GeogELlipsoidGeoKey.  For example Ellipse_Clarke_1866.	
	short	Datum;		// Datum from GeogGeodeticDatumGeoKey tag. For example Datum_WGS84

    short	ProjCode;     // Projection id from ProjectionGeoKey.  For example Proj_UTM_11S.
	short 	Zone;		  // UTM, or State Plane Zone number, zero if not known, output Only.
    short	CTProjection; // GeoTIFF identifier for underlying projection method.  While some of these values have corresponding vlaues in EPSG (Projection field), others do not.  For example CT_TransverseMercator.  
	short	nProjParms;						// Number of projection parameters in ProjParm and ProjParmId.
	int		ProjParmId[MAX_GTIF_PROJPARMS]; // Projection parameter identifier.  For example ProjFalseEastingGeoKey. The value will be 0 for unused table entries. 
	double	ProjParm[MAX_GTIF_PROJPARMS];   // Projection parameter value.  The identify of this parameter is established from the corresponding entry in ProjParmId.  The value will be measured in meters, or decimal degrees if it is a linear or angular measure. 
	
	double	SemiMajor;  // The length of the semi major ellipse axis in meters.
	double	SemiMinor;  // The length of the semi minor ellipse axis in meters.
}GEO_PROJPAR;

#endif


/* 
地理信息设置方法如下：
{
    CWuDPGImage imgFile;
    ....

    double mtrx[6];
    mtrx[0] = cos(kap)*gsd; mtrx[1] =  sin(kap)*gsd;
    mtrx[2] = sin(kap)*gsd; mtrx[3] = -cos(kap)*gsd;
    mtrx[4] = startX; 
    mtrx[5] = startY;

    IMGEXTINF extInf;
    extInf.extType = ET_GEOINF;
    extInf.pExtDat = mtrx;

    imgFile.SetExtInfo( &extInf,sizeof(extInf) );

    ....

    imgFile.Close();

    // 以上例子中  startX 和 startY 是 minX,maxY (左上角角点)    
}
地理信息+投影信息设置方法如下：
{        
    CWuDPGImage imgFile;
    ....
	
	GEO_PROJPAR proPar; memset( &proPar,0,sizeof(proPar) );
	proPar.mtrx[0] = cos(kap)*gsd; proPar.mtrx[1] =  sin(kap)*gsd;
    proPar.mtrx[2] = sin(kap)*gsd; proPar.mtrx[3] = -cos(kap)*gsd;
    proPar.mtrx[4] = startX; 
    proPar.mtrx[5] = startY;
	proPar.Model   = ModelTypeProjected;
	proPar.PCS	   = PCS_WGS84_UTM_zone_1N + 48;
	proPar.Datum   = Datum_WGS84;
	proPar.Ellipsoid   = Ellipse_WGS_84; 
	proPar.ProjCode    = Proj_UTM_zone_1N + 48;

    IMGEXTINF extInf;
    extInf.extType = ET_GEOINF_PROJ;
    extInf.pExtDat = (BYTE*)&proPar;

    imgFile.SetExtInfo( &extInf,sizeof(extInf) );

    ....
    imgFile.Close();    
}
*/

#ifndef _IMGEXTINF
#define _IMGEXTINF
typedef struct tagIMGEXTINF
{
    UINT  extType; // EXT_TYPE
    BYTE* pExtDat;
    
}IMGEXTINF;
#else
#pragma message("StDPGImage.h, Warning: IMGEXTINF alread define, be sure it was define as: struct tagIMGEXTINF{ UINT  extType;BYTE* pExtDat; }. \
               \nStDPGImage.h, 警告:类型 IMGEXTINF 已经定义过,请确保其定义为: struct tagIMGEXTINF{ UINT  extType;BYTE* pExtDat; }.") 
#endif

class WUDPGIMAGE_LIB CWuDPGImage : public CSpVZImage
{
public:
    CWuDPGImage();
    virtual ~CWuDPGImage();

    virtual CSpVZImage*		Clone(){ CWuDPGImage *p = new CWuDPGImage; p->Copy(this); return p; };
	virtual void			Copy( CWuDPGImage* p){ memcpy( this,p,sizeof(CWuDPGImage) ); };
	virtual void			Reset(){ Close();    };
	virtual bool			Init(){ return true; };	
	
    //!数据压缩模式
    enum COMP_TYPE{ CT_NONE=0,CT_LZW=1,CT_JPG=2,CT_ZIP=3,CT_LOG=4, };
    //!采样（波段）存放模式
    enum SAMP_STOR{ SS_NONE=0,SS_BIP=1,SS_BIQ=2, };

    virtual BOOL		Open ( LPCSTR lpstrPathName,UINT flag=modeRead,int maxBufSize=-1,CSpVZImage *pImgAcs=NULL );
	virtual void		Close();

    //!For Compress
    virtual BOOL        SetCompress( COMP_TYPE compType ){
        m_nCompType=compType;       if (m_pImgAcs)((CWuDPGImage*)m_pImgAcs)->SetCompress(compType);       UpdateImgBuf(); return (m_nCompType==compType)?TRUE:FALSE; };
    virtual BOOL        SetCompQuality( WORD compQuality=90 ){
        m_nCompQuality=compQuality; if (m_pImgAcs)((CWuDPGImage*)m_pImgAcs)->SetCompQuality(compQuality); UpdateImgBuf(); return (m_nCompQuality==compQuality)?TRUE:FALSE; };

    //!For Read .
    virtual BOOL        Set16_to_8ColorTab( WORD *pColorTab,int sampleIdx=0 ){ 
        return m_pImgAcs?((CWuDPGImage*)m_pImgAcs)->Set16_to_8ColorTab ( pColorTab,sampleIdx ):FALSE; };

    //!获取影像每像素的采样数（波段数）
	/**
	*@return 影像像素采样数（波段数）。如：全色影像一般为1 , RGB彩色一般为 3 , RGBA 为 4
	*/
	inline const  int GetPixelSamples(){ return GetPixelBytes(); };
    //!设定每像素的采样数（波段数）
	/**
    设定每像素的采样数（波段数），只有新建影像时此函数才可以使用
	*@param  int nPixelSamples 每像素的采样数
	*@return 无
	*/
    inline void  SetPixelSamples(int nPixelSamples){ SetPixelBytes(nPixelSamples); };

    //!获取影像每个采样的字节数
	/**
	*@return 影像每个采样的字节数。如：8 bits 的影像为1 , 11bits,12bits,16bits影像为2
	*/
	inline const  int GetSampleBytes(){ return m_nSampleBytes; };
    //!设定影像每个采样的字节数
	/**
    设定影像每个采样的字节数，只有新建影像时此函数才可以使用
	*@param  int nSampleBytes 影像每个采样的字节数
	*@return 无
	*/
    inline void  SetSampleBytes(int nSampleBytes){ 
        m_nSampleBytes=nSampleBytes;if(m_pImgAcs)((CWuDPGImage*)m_pImgAcs)->SetSampleBytes(nSampleBytes); UpdateImgBuf(); };

    //!获取影像采样（波段）数据存放模式
    /**
	*@return 影像采样（波段）数据存放模式。如：BIP 为 0, BSQ 为 1 ,BIL 为 2
	*/
    inline SAMP_STOR  GetSampleStorage(){ return (SAMP_STOR)m_nSampleStor; };
    //!设定影像采样（波段）数据存放模式
    /**
    设定影像采样（波段）数据存放模式，只有新建影像时此函数才可以使用
	*@param  SAMP_MODE nSampleModes 影像采样（波段）数据存放模式 如：BIP 为 0, BSQ 为 1 ,BIL 为 2
	*@return 无
	*/
    inline void  SetSampleStorage(SAMP_STOR nSampleStorage){
        m_nSampleStor=nSampleStorage; if(m_pImgAcs)((CWuDPGImage*)m_pImgAcs)->SetSampleStorage(nSampleStorage); UpdateImgBuf(); };

    //!For Pyramid Information default value is: 1, 2, 4, 8, 16, 32, 64,128,256,512 ...
    inline BOOL         SetPymZmRate( int pymLayers=1,WORD *pPymZmRate=NULL );
    inline const WORD*  GetPymZmRate( int& pymLayers );
        
    //! For Block Information 
    virtual BOOL        SetBlockWid(WORD blkWid){ return m_pImgAcs?((CWuDPGImage*)m_pImgAcs)->SetBlockWid(blkWid):FALSE; };
    virtual BOOL        SetBlockHei(WORD blkHei){ return m_pImgAcs?((CWuDPGImage*)m_pImgAcs)->SetBlockHei(blkHei):FALSE; };
    virtual const WORD  GetBlockWid(){ return m_pImgAcs?((CWuDPGImage*)m_pImgAcs)->GetBlockWid():0; };
    virtual const WORD  GetBlockHei(){ return m_pImgAcs?((CWuDPGImage*)m_pImgAcs)->GetBlockHei():0; };

    //! For Read and Write
    virtual BOOL ReadEx ( BYTE* pBuf,int rowIdx,SAMP_STOR stor=SS_BIP,int pymLayer=0 ){ 
        return m_pImgAcs?((CWuDPGImage*)m_pImgAcs)->ReadEx (pBuf,rowIdx,stor,pymLayer):Read(pBuf,rowIdx); };
	virtual BOOL WriteEx( BYTE* pBuf,int rowIdx,SAMP_STOR stor=SS_BIP,int pymLayer=0 ){
        return m_pImgAcs?((CWuDPGImage*)m_pImgAcs)->WriteEx(pBuf,rowIdx,stor,pymLayer):Write(pBuf,rowIdx); };
    virtual BOOL ReadEx ( BYTE* pBuf,int sRow,int sCol,int rows,int cols,SAMP_STOR stor=SS_BIP,int pymLayer=0 ){ 
        return m_pImgAcs?((CWuDPGImage*)m_pImgAcs)->ReadEx ( pBuf,sRow,sCol,rows,cols,stor,pymLayer ):Read(pBuf,m_nPixelBytes,sRow,sCol,rows,cols); }
    virtual BOOL WriteEx( BYTE* pBuf,int sRow,int sCol,int rows,int cols,SAMP_STOR stor=SS_BIP,int pymLayer=0 ){ 
        return m_pImgAcs?((CWuDPGImage*)m_pImgAcs)->WriteEx( pBuf,sRow,sCol,rows,cols,stor,pymLayer ):FALSE; }

    //////////////////////////////////////////////////////////////////////////////////////////////
    // 其他接口
    //////////////////////////////////////////////////////////////////////////////////////////////
    //!For Extend Information
    virtual BOOL		SetExtInfo(const BYTE* pInf,int infSize){ return m_pImgAcs?((CWuDPGImage*)m_pImgAcs)->SetExtInfo(pInf,infSize):FALSE; };
    virtual const BYTE* GetExtInfo(int& infSize){ return m_pImgAcs?((CWuDPGImage*)m_pImgAcs)->GetExtInfo(infSize):FALSE; };

    virtual BOOL CustomRead (BYTE* pBuf,WPARAM wParam,LPARAM lParam){ return m_pImgAcs?((CWuDPGImage*)m_pImgAcs)->CustomRead (pBuf,wParam,lParam):FALSE; };
    virtual BOOL CustomWrite(BYTE* pBuf,WPARAM wParam,LPARAM lParam){ return m_pImgAcs?((CWuDPGImage*)m_pImgAcs)->CustomWrite(pBuf,wParam,lParam):FALSE; };

protected:

    //!创建金字塔影像
    /**
    创建金字塔影像,此函数是针对新建影像使用的。
    */
    virtual BOOL        CreatePyramid(){ return m_pImgAcs?((CWuDPGImage*)m_pImgAcs)->CreatePyramid():FALSE; };
    //!读影像子块
    virtual BOOL        ReadBlock ( BYTE *pBuf,int blkCol,int blkRow,int pymLayer=0 ){ return m_pImgAcs?((CWuDPGImage*)m_pImgAcs)->ReadBlock (pBuf,blkCol,blkRow,pymLayer):FALSE; };
    //!写影像子块
    virtual BOOL        WriteBlock( BYTE *pBuf,int blkCol,int blkRow,int pymLayer=0 ){ return m_pImgAcs?((CWuDPGImage*)m_pImgAcs)->WriteBlock(pBuf,blkCol,blkRow,pymLayer):FALSE; };
    
protected:

    WORD            m_nSampleBytes,m_nSampleStor;
    WORD            m_ExtPar[8];
    
    WORD            m_pPymZmRate[16];
    WORD            m_nPymLayers,m_nCompType;
    WORD            m_nCompQuality;

private:
	//!内部实现的接口实例
    CWuDPGImage*    m_pImgAcs0; 

};


#endif
