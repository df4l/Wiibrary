    const int adc1=0;
    const int offset1=0;
    const int origin1=0;
    const int length1=1280;
    const int amp1=100;
    const int period1=1;
    const float pas1=(period1*360.0f)/length1;
    float siny1 = offset1*pas1;

    const int adc2=1;
    const int offset2=0;
    const int origin2=0;
    const int length2=1280;
    const int amp2=40;
    const int period2=2;
    const float pas2=(period2*360.0f)/length2;
    float siny2 = offset2*pas2;

    const int adc3=-3;
    const int offset3=0;
    const int origin3=0;
    const int length3=1280;
    const int amp3=30;
    const int period3=1;
    const float pas3=(period3*360.0f)/length3;
    float siny3 = offset3*pas3;

    const int adc4=-7;
    const int offset4=0;
    const int origin4=0;
    const int length4=1280;
    const int amp4=70;
    const int period4=1;
    const float pas4=(period4*360.0f)/length4;
    float siny4 = offset4*pas4;


    void render_background()
    {
        const float old1=siny1;
        const float old2=siny2;
        const float old3=siny3;
        const float old4=siny4;


        for (u16 x=0; x<=640; x++) {
            siny1+=pas1;
            siny2+=pas2;
            siny3+=pas3;
            siny4+=pas4;

            GX_Begin(GX_LINES, GX_VTXFMT0, 2);
                GX_Position3f32(x, 0, 0);
                GX_Color1u32(0xFFFFFFFF);
                GX_Position3f32(x, (sin(DegToRad(siny1))*amp1+origin1)+(sin(DegToRad(siny2))*amp2+origin2)+(sin(DegToRad(siny3))*amp3+origin3)+(sin(DegToRad(siny4))*amp4+origin4)+240,  0);
                GX_Color1u32(0x808080FF);
            GX_End();
            GX_Begin(GX_LINES, GX_VTXFMT0, 2);
                GX_Position3f32(x, (sin(DegToRad(siny1))*amp1+origin1)+(sin(DegToRad(siny2))*amp2+origin2)+(sin(DegToRad(siny3))*amp3+origin3)+(sin(DegToRad(siny4))*amp4+origin4)+240,  0);
                GX_Color1u32(0x808080FF);
                GX_Position3f32(x, 480, 0);
                GX_Color1u32(0xFFFFFFFF);
            GX_End();

        }
        siny1=old1+(adc1*pas1*0.25f);
        siny2=old2+(adc2*pas2*0.25f);
        siny3=old3+(adc3*pas3*0.25f);
        siny4=old4+(adc4*pas4*0.25f);
    }

const u32 col[4] = {0xFFFFFFFF, 0xAAAAAAFF, 0x666666FF, 0xFF0000FF};

void draw_book()
{
    GX_Begin(GX_QUADS, GX_VTXFMT0, 24);
            GX_Position3f32(-1.0f,2.0f,0.8f);
            GX_Color1u32(col[0]);
            GX_Position3f32(-1.0f,-1.0f,0.8f);
            GX_Color1u32(col[0]);
            GX_Position3f32(1.0f,-1.0f,0.8f);
            GX_Color1u32(col[0]);
            GX_Position3f32(1.0f,2.0f,0.8f);
            GX_Color1u32(col[0]);

            GX_Position3f32(-1.0f,2.0f,1.0f);
            GX_Color1u32(col[3]);
            GX_Position3f32(-1.0f,-1.0f,1.0f);
            GX_Color1u32(col[0]);
            GX_Position3f32(1.0f,-1.0f,1.0f);
            GX_Color1u32(col[0]);
            GX_Position3f32(1.0f,2.0f,1.0f);
            GX_Color1u32(col[3]);

            GX_Position3f32(-1.0f,2.0f,1.0f);
            GX_Color1u32(col[1]);
            GX_Position3f32(1.0f,2.0f,1.0f);
            GX_Color1u32(col[1]);
            GX_Position3f32(1.0f,2.0f,0.8f);
            GX_Color1u32(col[1]);
            GX_Position3f32(-1.0f,2.0f,0.8f);
            GX_Color1u32(col[1]);

            GX_Position3f32(-1.0f,-1.0f,1.0f);
            GX_Color1u32(col[1]);
            GX_Position3f32(1.0f,-1.0f,1.0f);
            GX_Color1u32(col[1]);
            GX_Position3f32(1.0f,-1.0f,0.8f);
            GX_Color1u32(col[1]);
            GX_Position3f32(-1.0f,-1.0f,0.8f);
            GX_Color1u32(col[1]);

            GX_Position3f32(-1.0f,2.0f,1.0f);
            GX_Color1u32(col[2]);
            GX_Position3f32(-1.0f,2.0f,0.8f);
            GX_Color1u32(col[2]);
            GX_Position3f32(-1.0f,-1.0f,0.8f);
            GX_Color1u32(col[2]);
            GX_Position3f32(-1.0f,-1.0f,1.0f);
            GX_Color1u32(col[2]);

            //pages
            GX_Position3f32(1.0f,2.0f,1.0f);
            GX_Color1u32(col[0]);
            GX_Position3f32(1.0f,2.0f,0.8f);
            GX_Color1u32(col[2]);
            GX_Position3f32(1.0f,-1.0f,0.8f); 
            GX_Color1u32(col[2]);
            GX_Position3f32(1.0f,-1.0f,1.0f);
            GX_Color1u32(col[0]);
        GX_End();
}