#include "Model.h"
#include "WorldTransform.h"


/// <summary>
/// ���L�����̒e
/// </summary>
class PlayerBullet{
  
private:

  // ���[���h�ϊ��f�[�^
  WorldTransform worldTransform_;
  // ���f��
  Model* model_ = nullptr;
  // �e�N�X�`���n���h��
  uint32_t textureHandle_ = 0u;
  
public:
	
  /// <summary>
  /// ������
  /// </summary>
  void Initialize(Model* model, const Vector3& position);
 
  /// <summary>
  /// �X�V
  /// </summary>
  void Update();

  /// <summary>
  /// �`��
  /// </summary>
  void Draw(const ViewProjection& viewProjection);

};
