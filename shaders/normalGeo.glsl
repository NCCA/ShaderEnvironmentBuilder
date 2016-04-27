#version 330 core
layout(triangles) in;
layout(line_strip, max_vertices = 8) out;

in vec4 normal[];

uniform  float normalSize;
uniform  vec4 vertNormalColour;
uniform  vec4 faceNormalColour;
uniform bool drawFaceNormals;
uniform bool drawVertexNormals;
out vec4 perNormalColour;

void main()
{
    if (drawVertexNormals == true)
    {
        perNormalColour=vertNormalColour;

        for(int i = 0; i<gl_in.length(); ++i)
        {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
        gl_Position =   gl_in[i].gl_Position +( normal[i] * normalSize);
        EmitVertex();
        EndPrimitive();
        }
    }
    if (drawFaceNormals == true)
    {
        perNormalColour=faceNormalColour;

        vec4 cent = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0;
        vec3 face_normal = normalize(cross(gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz,
                                           gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz));

        gl_Position =  cent;
        EmitVertex();
        gl_Position =  (cent + vec4(face_normal * normalSize, 0.0));
        EmitVertex();
        EndPrimitive();
    }
}


