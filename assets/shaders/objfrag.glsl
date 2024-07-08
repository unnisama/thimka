#version 430
out vec4 FragColor;
uniform float deltatime;
uniform float time;
uniform float freq;
uniform sampler2D u_texture;
uniform int width = 0;
uniform int height = 0;
uniform int radius = 5;
in vec2 TexCoord;

float map(float value, float min1, float max1, float min2, float max2) {
    return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

float mapsin(float v){
    return map(sin(v), -1.0, 1.0, 0.2, 0.8);
}

vec4 GetInbound(vec2 pos, vec2 off){
    vec2 poscopy = pos;
    poscopy += off;

    if(poscopy.x < 0.0 || poscopy.x > 1.0 || poscopy.y < 0.0 || poscopy.y > 1.0){
        return vec4(0.0, 0.0, 0.0, -1.0);
    }

    return texture(u_texture, poscopy);
}

vec4 BlurPixel(int rad){
    float pixwidth = 1.0/width;
    float pixheight = 1.0/height;

    float rid = float((rad-1)/2);
    vec2 subty = vec2(rid*pixwidth, rid*pixheight);

    vec2 posp = TexCoord - subty;

    float count = 0.0;
    vec4 outcolor = vec4(0.0);

    for(int i = 0; i < rad; i++){
        for(int j = 0; j < rad; j++){
            vec4 retcolor = GetInbound(posp, vec2(float(i)*pixwidth, float(j)*pixheight));
            if(retcolor.a == -1){
                continue;
            }
            outcolor += retcolor;
            count += 1.0;
        }
    }

    vec4 blur = outcolor/count;

    return blur;
}

int isInRange(vec4 v, float r, vec4 vc){
    int outt = 0;
    if (v.r+r > vc.r && v.r-r < vc.r){
        outt += 1;
    }
    if (v.g+r > vc.g && v.g-r < vc.g){
        outt += 1;
    }
    if (v.b+r > vc.b && v.b-r < vc.b){
        outt += 1;
    }
    return outt;
}

void main()
{

    vec4 color1 = texture(u_texture, TexCoord);
    
    FragColor = color1;
}
