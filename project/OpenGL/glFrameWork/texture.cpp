#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../application/stb_image.h"

Texture::Texture(const std::string& path, unsigned int unit)
{
    m_unit = unit;
    //读取图片
    int channels;

    //反转Y轴
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &channels, STBI_rgb_alpha);

    //生成纹理并激活单元绑定
    GL_CALL(glGenTextures(1, &m_texture));
    //激活
    GL_CALL(glActiveTexture(GL_TEXTURE0 + m_unit));
    //绑定
    GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture));

    //传输纹理数据,开辟显存
    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));

    //释放数据
    stbi_image_free(data);

    //设置纹理过滤方式
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

    //设置纹理包裹方式
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));//u方向
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));//v方向
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
