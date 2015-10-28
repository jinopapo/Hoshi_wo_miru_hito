#ifndef __ISCENECHANGER_H_INCLUDED__
#define __ISCENECHANGER_H_INCLUDED__
typedef enum {
    eScene_Menu,    //���j���[���
    eScene_Game,    //�Q�[�����
    eScene_Config,  //�ݒ���
	eScene_StartStage, //�ŏ��̃X�e�[�W
	eScene_Mamusu, //�܂ނ���
	eScene_Deusu,
	eScene_Op,      //�I�[�v�j���O
    eScene_None,    //����
} eScene ;

//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class ISceneChanger {
public:
    virtual ~ISceneChanger() = 0;
    virtual void ChangeScene(eScene NextScene) = 0;//�w��V�[���ɕύX����
};

#endif