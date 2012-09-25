#include "Record.h"

void Image::greyToRGB(
        int(*rFunc)(int, int, int, int, int), 
        int(*gFunc)(int, int, int, int, int), 
        int(*bFunc)(int, int, int, int, int), 
        int r_0, int g_0, int b_0, int range) {

    if (img == NULL)
        return;

    int w = img->width();
    int h = img->height();
    int r, g, b;
    QRgb rgb;

    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j) {
            rgb = tempImg->pixel(i, j);

            r = rFunc(qRed(rgb), r_0, g_0, b_0, range);
            g = gFunc(qGreen(rgb), r_0, g_0, b_0, range);
            b = bFunc(qBlue(rgb), r_0, g_0, b_0, range);

            img->setPixel(i, j, qRgb(r, g, b));
        }
    getHistogram();
    update();
}

void Image::greyToPseudoColor(int range, int r, int g, int b) {
    int (*rFunc)(int, int, int, int, int) = redFunc;
    int (*gFunc)(int, int, int, int, int) = greenFunc;
    int (*bFunc)(int, int, int, int, int) = blueFunc;

    greyToRGB(rFunc, gFunc, bFunc, r, g, b, range);
}

int redFunc(int grey, int r, int g, int b, int range) {
    if (grey >= 0 && grey < range)
        return grey + (float)(255 - grey) * r / (r + g + b);
    return grey;
}

int greenFunc(int grey, int r, int g, int b, int range) {
    if (grey >= 0 && grey < range)
        return grey + (float)(255 - grey) * g / (r + g + b);
    return grey;
}

int blueFunc(int grey, int r, int g, int b, int range) {
    if (grey >= 0 && grey < range)
        return grey + (float)(255 - grey) * b / (r + g + b);
    return grey;
}

void Image::addBorder() {
    int width = img->width();
    int height = img->height();

    for (int n = 0; n < 5; ++n) {
        for (int i = 0; i < width; ++i) {
            img->setPixel(i, n, qRgb(0, 0, 255));
            img->setPixel(i, height - 1 - n, qRgb(0, 0, 255));
        }

        for (int i = 0; i < height; ++i) {
            img->setPixel(n, i, qRgb(0, 0, 255));
            img->setPixel(width - 1 - n, i, qRgb(0, 0, 255));
        }
    }
}

// to HSI color model 
QImage* Image::toHSI(QImage* image){
    int width = img->width();
    int height = img->height();

    QRgb rgb;
    int R, G, B;
    int H, S, I;

    QImage* newImg = new QImage(width, height, image->format());
    if (newImg == NULL)
        return NULL;

    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j){
            rgb = img->pixel(i, j);
            R = qRed(rgb);
            G = qGreen(rgb);
            B = qBlue(rgb);

            double sqrt_x = sqrt((R - G) * (R - G) + (R - B) * (G - B));
            double acos_x = (sqrt_x != 0)? acos(((R - G) - (R - B)) / (sqrt_x * 2)) : PI / 2;
            int degree = 180 * acos_x / PI;
            H = (B <= G)? degree : 360 - degree;
            S = (R + G + B != 0)? 360 * (1 - 3 * min(min(R, G), B) / (double)(R + G + B)) : 360;
            I = 120 * (R + G + B) / 256;

            H = quantizationH(H);
            S = quantizationS(S);
            I = quantizationI(I);

            newImg->setPixel(i, j, qRgb(H, S, I));
        }
    return newImg;
}

QVector<QVector<double> > Image::histogram(QImage image){
    int width = image.width();
    int height = image.height();
    QRgb hsi;
    int H, S, I;

    QVector<double> _histogramH(N_Level, 0);
    QVector<double> _histogramS(N_Level, 0);
    QVector<double> _histogramI(N_Level, 0);

    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j){
            hsi = image.pixel(i, j);
            H = qRed(hsi);
            S = qGreen(hsi);
            I = qBlue(hsi);

            ++_histogramH[H];
            ++_histogramS[S];
            ++_histogramI[I];
        }

    double MN = width * height;
    for (int i = 0; i < N_Level; ++i){
        _histogramH[i] = _histogramH[i] * RANGE / MN;
        _histogramS[i] = _histogramS[i] * RANGE / MN;
        _histogramI[i] = _histogramI[i] * RANGE / MN;
    }

    QVector<QVector<double> > histogramHSI(3);
    histogramHSI[0] = _histogramH;
    histogramHSI[1] = _histogramS;
    histogramHSI[2] = _histogramI;
    return histogramHSI;
}

QVector<QImage> Image::partition(QImage* image){
    if (image == NULL)
        return QVector<QImage>();

    int width = image->width();
    int height = image->height();

    int nx = width  / N_WH;
    int ny = height / N_WH;

    QVector<QImage> subImages(N_Partition);
    int x, y, w, h;

    w = nx * N_WH / 2;
    h = ny * N_WH / 2;
    x = 0;
    y = 0;
    subImages[0] = image->copy(x, y, w, h);
    x = width  - w;
    subImages[1] = image->copy(x, y, w, h);
    y = height - h;
    subImages[2] = image->copy(x, y, w, h);
    x = 0;
    subImages[3] = image->copy(x, y, w, h);

    w = nx * N_WH / 2;
    h = ny * N_WH / 2;
    x = w / 2;
    y = 0;
    subImages[4] = image->copy(x, y, w, h);
    y = height - h;
    subImages[5] = image->copy(x, y, w, h);
    x = 0;
    y = h / 2;
    subImages[6] = image->copy(x, y, w, h);
    x = width - w;
    subImages[7] = image->copy(x, y, w, h);

    x = w / 2;
    subImages[8] = image->copy(x, y, w, h);

    subImages[9] = image->copy(0, 0, width, height);

    return subImages;
}

QVector<QVector<QVector<double> > > Image::histograms(QVector<QImage> subImgs){
    QVector<QVector<QVector<double> > > _histograms(N_Partition);

    for (int i = 0; i < N_Partition; ++i)
        _histograms[i] = histogram(subImgs[i]);
    return _histograms;
}

void Image::saveCharacteristic(){
    /*QImage* image = toHSI(img);

      QVector<QImage> subImages = partition(image);
      QVector<QVector<QVector<double> > > _histograms = histograms(subImages);

      QFile data("imgDB.txt");
      if (!data.open(QIODevice::Append))
      return;
      QTextStream out(&data);
      int end1 = _histograms.size();
      int end2 = _histograms[0].size();
      int end3 = _histograms[0][0].size();
      for (int i = 0; i < end1; ++i){
      for (int r = 0; r < end2; ++r){
      for (int j = 0; j < end3; ++j)
      out << _histograms[i][r][j] << " ";
      out << "/";
      }
      out << "#";
      }

      out << "@";
      out << img->width() << " " << img->height() << "@";
      out << imgName << "\n";

      data.close();*/
    match();
}

QStringList Image::match(){
    QImage* image = toHSI(img);

    QVector<QImage> subImages = partition(image);
    QVector<QVector<QVector<double> > > _histograms = histograms(subImages);

    Record record(_histograms, img->width(), img->height(), imgName);
    QVector<Record> records = ImgRecords();
    return matchedImgsName(record, records);
}

int quantizationH(int level){
    if ((level >= 316 && level <= 360 ) || (level >= 0 && level <= 20))//65
        return 0;
    else if (level >= 21 && level <= 40)//20
        return 1;
    else if (level >= 41 && level <= 75)//35
        return 2;
    else if (level >= 76 && level <= 155)//80
        return 3;
    else if (level >= 156 && level <= 190)//35
        return 4;
    else if (level >= 191 && level <= 270)//80
        return 5;
    else if (level >= 271 && level <= 295)//25
        return 6;
    else//20
        return 7;

    /*if ((level >= 339 && level <= 360 ) || (level >= 0 && level <= 23))//65
      return 0;
      else if (level >= 24 && level <= 68)
      return 1;
      else if (level >= 69 && level <= 113)
      return 2;
      else if (level >= 114 && level <= 158)
      return 3;
      else if (level >= 159 && level <= 203)
      return 4;
      else if (level >= 204 && level <= 248)
      return 5;
      else if (level >= 249 && level <= 293)
      return 6;
      else//294-338
      return 7;*/
}

int quantizationS(int level){
    if (level >= 0 && level <= 45 )//65
        return 0;
    else if (level >= 46 && level <= 90)
        return 1;
    else if (level >= 91 && level <= 135)
        return 2;
    else if (level >= 136 && level <= 180)
        return 3;
    else if (level >= 181 && level <= 225)
        return 4;
    else if (level >= 226 && level <= 270)
        return 5;
    else if (level >= 271 && level <= 315)
        return 6;
    else//294-338
        return 7;
}

int quantizationI(int level) { 
    return quantizationS(level); 
}

double histogramCompare(QVector<double> histogram1, QVector<double> histogram2){
    int size = histogram1.size();
    double dis = 0;
    for (int i = 0; i < size; ++i)
        dis += fabs(histogram1[i] - histogram2[i]);
    return sqrt(dis);
}

double imgMatching(QVector<QVector<QVector<double> > > imghistograms1,
        QVector<QVector<QVector<double> > > imghistograms2){
    double similarityH = 0;
    double similarityS = 0;
    double similarityI = 0;
    int end = imghistograms1.size();

    for (int i = 0; i < end; ++i){
        similarityH += WEIGHT[i] * histogramCompare(imghistograms1[i][0], imghistograms2[i][0]);
        similarityS += WEIGHT[i] * histogramCompare(imghistograms1[i][1], imghistograms2[i][1]);
        similarityI += WEIGHT[i] * histogramCompare(imghistograms1[i][2], imghistograms2[i][2]);
    }

    return similarityH * H_Weight + similarityS * S_Weight + similarityI * I_Weight;
}

Record::Record(QString info){
    QStringList subStr = info.split("@");

    fname = subStr[2];

    QStringList size = subStr[1].split(" ");
    width  = size[0].toInt();
    height = size[1].toInt();
    histograms = QVector<QVector<QVector<double> > >(N_Partition);

    QStringList histogramsInfo = subStr[0].split("#");
    for (int i = 0; i < N_Partition; ++i){
        QStringList hsi = histogramsInfo[i].split("/");
        histograms[i] = QVector<QVector<double> >(3);

        for (int r = 0; r < 3; ++r){
            QStringList histogram = hsi[r].split(" ");
            histograms[i][r] = QVector<double>(N_Level);

            for (int j = 0; j < N_Level; ++j){
                histograms[i][r][j] = histogram[j].toDouble();
            }
        }
    }
}

Record::Record(QVector<QVector<QVector<double> > > _histograms, int w, int h, QString fn){
    histograms = _histograms;
    width = w;
    height = h;
    fname = fn;
}

QVector<Record> ImgRecords(){
    QVector<Record> records;
    QFile imgDataBase("imgDB.txt");

    if (imgDataBase.open(QIODevice::ReadOnly)){
        QTextStream in(&imgDataBase);
        while(!in.atEnd()){
            QString info = in.readLine();
            Record imgRecord(info);
            records.append(imgRecord);
        }
    }
    imgDataBase.close();
    return records;
}

int similarityCmp(Record2 r1, Record2 r2){
    if(r1.similarity < r2.similarity)
        return 1;
    else
        return 0;
}

QStringList matchedImgsName(Record image, QVector<Record> imgDB) {
    int size = imgDB.size();
    QStringList nameList;
    QVector<Record2> similarityDB = QVector<Record2>(size);

    for (int i = 0; i < size; ++i){
        similarityDB[i].similarity =
            imgMatching(image.histograms, imgDB[i].histograms);
        similarityDB[i].fname = imgDB[i].fname;
    }

    sort(similarityDB.begin(), similarityDB.end(), similarityCmp);
    for(int i = 0; i < size; ++i)
        nameList.append(similarityDB[i].fname);

    return nameList;
}
