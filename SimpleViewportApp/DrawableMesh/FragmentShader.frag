varying vec3 m_vertex;
varying vec3 m_normal;

uniform vec3 colourVector;
uniform bool normalMapOn;

void main(void)
{
    //vec3 color = vec3(1.0, 0.0, 0.0);
    vec3 color = colourVector;
    vec3 lightDir = vec3(0.0, 0.0, -1.0);
    float diffuse = dot(m_normal, -lightDir);
    vec3 viewDir = normalize(m_vertex);
    vec3 reflectedLightDir = reflect(lightDir, m_normal);
    float specular = max(dot(reflectedLightDir, -viewDir), 0.0);
    float specularAmount = 0.05;
    float diffuseAmount = 0.75;
    float ambientAmount = 1.0 - diffuseAmount;
    if(normalMapOn){
        gl_FragColor = vec4(m_normal, 1.0);
    }else{
        gl_FragColor = vec4(color * ambientAmount + color * diffuse * diffuseAmount + specular * specularAmount, 1.0);
    }
}
