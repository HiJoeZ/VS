#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../application/stb_image.h"

Texture::Texture(const std::string& path, unsigned int unit)
{
    m_unit = unit;
    //��ȡͼƬ
    int channels;

    //��תY��
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &channels, STBI_rgb_alpha);

    //�����������Ԫ��
    GL_CALL(glGenTextures(1, &m_texture));
    //����
    GL_CALL(glActiveTexture(GL_TEXTURE0 + m_unit));
    //��
    GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture));

    //������������,�����Դ�
    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));

    //�ͷ�����
    stbi_image_free(data);

    //����������˷�ʽ
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

    //�������������ʽ
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));//u����
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));//v����
}

Texture::~Texture()
{
    if (m_texture != 0)
    {
        GL_CALL(glDeleteTextures(1,&m_texture));
        m_texture = 0;
    }
}

void Texture::bind()
{
    GL_CALL(glActiveTexture(GL_TEXTURE0 + m_unit));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture));
}
