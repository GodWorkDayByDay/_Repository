#include "milc.h"
#include <QDebug>
#include <QFile>
#include <QMessageBox>

MILC::MILC()
{
    QFile file("./log_unit/log.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString data = QString(file.readAll());
    unit = data.toDouble();

    Time = 0.0;
    x = 0.0, y = 0.0, angle = 0.0;
    Score = 0.0;
    XOrg = YOrg = 0.0;
    b_model = b_source = Q_NULLPTR;
    modelID = 1;

    MappAllocDefault(M_DEFAULT, &MilApplication, &MilSystem, &MilDisplay, M_NULL, M_NULL);
}

MILC::~MILC()
{
    delete []b_model;
    delete []b_source;

    MappFreeDefault(MilApplication, MilSystem, MilDisplay, M_NULL, M_NULL);
}

bool MILC::MilSearch(double &find_x, double &find_y)
{
    bool isSuccess = true;

    /*********************************  start *********************************************/

    MIL_CONST_TEXT_PTR model;
    if (modelID == 0)
        model = MIL_TEXT("./model.jpg");
    else if (modelID == 1)
        model = MIL_TEXT("./model1.jpg");
    else if(modelID == 2)
        model = MIL_TEXT("./model2.jpg");

    MIL_CONST_TEXT_PTR file = MIL_TEXT("./source.jpg");

    MIL_INT width = 0, s_width = 0;
    MIL_INT height = 0, s_height = 0;

    MbufRestore(model, MilSystem, &ImageModel);
    MbufInquire(ImageModel, M_SIZE_X, &width);
    MbufInquire(ImageModel, M_SIZE_Y, &height);
    b_model = new BYTE[width * height * sizeof(BYTE) * 3];
    MbufGet(ImageModel, b_model);
    MbufFree(ImageModel);

    MbufRestore(file, MilSystem, &ImageSource);
    MbufInquire(ImageSource, M_SIZE_X, &s_width);
    MbufInquire(ImageSource, M_SIZE_Y, &s_height);
    b_source = new BYTE[s_width * s_height * sizeof(BYTE) * 3];
    MbufGet(ImageSource, b_source);
    MbufFree(ImageSource);

    /***********************************  end   ****************************************/

    MbufAlloc2d(MilSystem,
                width,
                height,
                8 + M_UNSIGNED,
                M_IMAGE + M_PROC + M_DISP,
                &ImageModel);

    MbufPut(ImageModel, b_model);

    MpatAllocModel(MilSystem, ImageModel, 0, 0,
                   width, height, M_NORMALIZED, &Model);


    MbufAlloc2d(MilSystem,
                s_width,
                s_height,
                8 + M_UNSIGNED,
                M_IMAGE + M_DISP + M_PROC,
                &ImageSource);

    MbufPut(ImageSource, b_source);

    MpatSetAccuracy(Model, M_HIGH);
    MpatSetSpeed(Model, M_HIGH);

    MpatPreprocModel(ImageSource, Model, M_DEFAULT);
    MpatAllocResult(MilSystem, 1L, &Result);

    MpatFindModel(ImageModel, Model, Result);
    MpatFindModel(ImageSource, Model, Result);

    if (MpatGetNumber(Result, M_NULL) == 1L)
    {
        MpatGetResult(Result, M_POSITION_X, &x);
        MpatGetResult(Result, M_POSITION_Y, &y);
        MpatGetResult(Result, M_SCORE, &Score);

        MpatInquire(Model, M_ORIGINAL_X, &XOrg);
        MpatInquire(Model, M_ORIGINAL_Y, &YOrg);

        if (modelID == 0)
        {
            find_x = (x - s_width / 2);
            find_y = y;
        }
        else
        {
            find_x = 1.0 * (x - s_width / 2) * unit;
            find_y = -1.0 * (y - s_height / 2) * unit;
        }
    }
    else
    {
        find_x = -1;
        find_y = -1;

        isSuccess = false;
    }

    MpatFree(Result);
    MpatFree(Model);
    MbufFree(ImageModel);
    MbufFree(ImageSource);

    return isSuccess ? true : false;
}

