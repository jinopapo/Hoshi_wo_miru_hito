#ifndef __ISCENECHANGER_H_INCLUDED__
#define __ISCENECHANGER_H_INCLUDED__
typedef enum {
    eScene_Menu,    //メニュー画面
    eScene_Game,    //ゲーム画面
    eScene_Config,  //設定画面
	eScene_StartStage, //最初のステージ
	eScene_Mamusu, //まむす村
	eScene_Deusu,
	eScene_Op,      //オープニング
    eScene_None,    //無し
} eScene ;

//シーンを変更するためのインターフェイスクラス
class ISceneChanger {
public:
    virtual ~ISceneChanger() = 0;
    virtual void ChangeScene(eScene NextScene) = 0;//指定シーンに変更する
};

#endif