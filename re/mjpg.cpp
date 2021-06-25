#include <string>

#include "mjpg.hpp"

using namespace std;

string ContentType = "HTTP/1.0 200 OK\r\n"
    + "Server: en.code-bude.net example server\r\n"
    + "Cache-Control: no-cache\r\n"
    + "Cache-Control: private\r\n" 
    + "Content-Type: multipart/x-mixed-replace;boundary=--boundary\r\n\r\n";

string get_boundary_string( int size ) {
    string bs;

    bs = "--boundary\r\n"
        + "Content-Type: image/jpeg\r\n"
        + "Content-Length: "
        + to_string( size )
        + "\r\n\r\n";
    return bs;
}   

int write_mjpeg()
{
#ifdef IGNORE
    int rc = write(sd, ContentType.c_str(), ContentType.length());
    if (rc != 0) {
        cerr << "Failed to write content type for MJPEG" << endl;
    }

    while ( img = imgQ.back() ) {
        imgQ.pop_back();

        // Image to Byte Array via OPENCV Method
        std::vector<uchar> buff;
        imencode(".jpg", img, buff);
        std::string content(buff.begin(), buff.end());

        img.length();

        QByteArray BoundaryString = ("--boundary\r\n"           \
                                     "Content-Type: image/jpeg\r\n"     \
                                     "Content-Length: ");

        BoundaryString.append(QString::number(CurrentImg.length()));
        BoundaryString.append("\r\n\r\n");

        m_TcpHttpClient->write(BoundaryString);
        m_TcpHttpClient->write(CurrentImg); // Write The Encoded Image
        
        m_TcpHttpClient->flush();
    }
#endif // IGNORE 
    return 0;
}
