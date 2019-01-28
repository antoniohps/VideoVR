#ifndef QTCVVIEWERGL_H
#define QTCVVIEWERGL_H

#include "qtcvviewergl_global.h"
#include "Image.h"

#include <QOpenGLWidget>
#include <opencv2/core/core.hpp>

class QTCVVIEWERGLSHARED_EXPORT CQtOpenCVViewerGl : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit CQtOpenCVViewerGl(QWidget *parent = 0);

signals:
    void    imageSizeChanged( int outW, int outH ); /// Used to resize the image outside the widget

public slots:
    void    openFile(const QString& imageFile); ///Used to open an image by name
    bool    showImage(const cv::Mat &image); /// Used to set the image to be viewed
    bool    showImage(const ip::Image &image); /// Used to set the image to be viewed


protected:
    void 	initializeGL(); /// OpenGL initialization
    void 	paintGL(); /// OpenGL Rendering
    void 	resizeGL(int width, int height);        /// Widget Resize Event

    void        updateScene();
    void        renderImage();

private:
    bool        mSceneChanged;          /// Indicates when OpenGL view is to be redrawn

    QImage      mRenderQtImg;           /// Qt image to be rendered
    cv::Mat     mOrigImage;             /// original OpenCV image to be shown

    QColor      mBgColor;		/// Background color

    int         mOutH;                  /// Resized Image height
    int         mOutW;                  /// Resized Image width
    float       mImgRatio;             /// height/width ratio

    int         mPosX;                  /// Top left X position to render image in the center of widget
    int         mPosY;                  /// Top left Y position to render image in the center of widget

};


#endif // QTCVVIEWERGL_H
