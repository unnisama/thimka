#version 430
out vec4 FragColor;
uniform float deltatime;
uniform float time;
uniform sampler2D u_texture;
in vec3 apos;
in vec2 TexCoord;
in vec3 vnormal;


float map(float value, float min1, float max1, float min2, float max2) {
    return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

float mapsin(float v){
    return map(sin(v), -1.0, 1.0, 0.2, 0.8);
}
float mapsininBetween(float v, float min_, float max_){
    return map(sin(v), -1.0, 1.0, min_, max_);
}

// vec4 GetInbound(vec2 pos, vec2 off){
//     vec2 poscopy = pos;
//     poscopy += off;

//     if(poscopy.x < 0.0 || poscopy.x > 1.0 || poscopy.y < 0.0 || poscopy.y > 1.0){
//         return vec4(0.0, 0.0, 0.0, -1.0);
//     }

//     return texture(u_texture, poscopy);
// }

// vec4 BlurPixel(int rad){
//     float pixwidth = 1.0/width;
//     float pixheight = 1.0/height;

//     float rid = float((rad-1)/2);
//     vec2 subty = vec2(rid*pixwidth, rid*pixheight);

//     vec2 posp = TexCoord - subty;

//     float count = 0.0;
//     vec4 outcolor = vec4(0.0);

//     for(int i = 0; i < rad; i++){
//         for(int j = 0; j < rad; j++){
//             vec4 retcolor = GetInbound(posp, vec2(float(i)*pixwidth, float(j)*pixheight));
//             if(retcolor.a == -1){
//                 continue;
//             }
//             outcolor += retcolor;
//             count += 1.0;
//         }
//     }

//     vec4 blur = outcolor/count;

//     return blur;
// }

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

vec3 palette(float t)
{
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(2.168, 1.728, 1.888);
    vec3 d = vec3(-0.032, 0.333, 0.667);
    return a + b*cos( 6.28318*(c*t+d) );
}

void main()
{
    // vec3 objectColor = texture(u_texture, TexCoord).rgb;
    // vec4 normalMapColor = texture(u_normal, TexCoord);


    // vec3 lightDir = normalize(lightPos - apos);
    // vec3 viewDir = normalize(viewpos - apos);
    // vec3 reflectDir = reflect(-lightDir, normalize(vnormal));

    // float normal = max(0.0, dot(texture(u_normal, TexCoord).xyz, lightDir));

    // float ambientStrength = 0.1;
    // vec3 ambient = ambientStrength * lightcolor;


    // float diff = max(dot(vnormal, lightDir), 0.0);
    // vec3 diffuse = diff * lightcolor;


    // float specularStrength = 0.3;
    // float shininess = 32.0;
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // vec3 specular = specularStrength * spec * lightcolor;
    


    // vec3 result = (ambient + diffuse + specular) * objectColor * normal;
    // float randomvalue = cos(apos.r) + cos(apos.g) + cos(apos.b);
    // randomvalue = 0.0f;
    vec3 tint = vec3(mapsin(apos.r), mapsin(apos.g), mapsin(apos.b));
    // vec2 TexCoord2 = TexCoord - 0.5;
    // //float max_radius = map(sin((time-randomvalue)*3.0), -1.0, 1.0, 0.01, 0.25);
    // float max_radius = 0.2;
    // float radius = TexCoord2.x * TexCoord2.x + TexCoord2.y * TexCoord2.y;

    vec2 uv = TexCoord * 2.0 - 1.0;
    // float siny = sin(time);
    // float cosx = cos(time);
    //vec2 rotatedTexCoord = vec2(uv.x * cosx - uv.y * siny, uv.x * siny + uv.y * cosx);
    
    float d = length(uv);
    float d0 = d;
    if (d > 0.7){
        discard;
    }
    d = sin(d*12.0+time*2.0)/20.0;
    d = abs(d);

    d = 0.1/d;


    FragColor = texture(u_texture, TexCoord);
    FragColor.rgb = FragColor.rgb * d * tint;
    FragColor.a = 0.7 - d0;

    // float siny = sin(time);
    // float cosx = cos(time);
    // if(d < radius){
    //     d = (radius - d) * (1.0/radius);
    //     vec2 rotatedTexCoord = 0.5 + (vec2(uv.x * cosx - uv.y * siny, uv.x * siny + uv.y * cosx) / 2.0);
    //     FragColor = texture(u_texture, rotatedTexCoord);
    //     if((FragColor.r + FragColor.g + FragColor.b)/3.0 < 0.19){
    //         discard;
    //     }
    //     FragColor = FragColor * tint;
    //     FragColor.a = d;
    // }else{
    //     discard;
    // }
    
}
