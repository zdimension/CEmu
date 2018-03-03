#ifndef HEXWIDGET_H
#define HEXWIDGET_H

#include <QtCore/QPoint>
#include <QtWidgets/QWidget>
#include <QtWidgets/QAbstractScrollArea>

class HexWidget : public QAbstractScrollArea {
    Q_OBJECT

public:
    explicit HexWidget(QWidget *parent = Q_NULLPTR);
    virtual ~HexWidget() { }

    void setBaseAddr(int address) { m_baseAddr = address; adjust(); }
    uint32_t baseAddr() { return static_cast<uint32_t>(m_baseAddr); }

    void setBytesPerLine(int bytes) { m_bytesPerLine = bytes; adjust(); }
    int bytesPerLine() { return m_bytesPerLine; }

    void setAsciiArea(bool area) { m_asciiArea = area; adjust(); }
    bool asciiArea() { return m_asciiArea; }

    void setScrollable(bool state) { m_scrollable = state; adjust(); }
    bool scrollable() { return m_scrollable; }

    void setAddr(int addr);
    void setCursorAddr(int address);
    uint32_t getAddr() { return static_cast<uint32_t>(m_addrCursor / 2); }

    void setData(const QByteArray &ba);
    void prependData(const QByteArray &ba);
    void appendData(const QByteArray &ba);
    const char *data() { return m_data.constData(); }

    int size() { return m_size; }

    int indexNotOf(const QByteArray &ba);
    int indexPrevOf(const QByteArray &ba);
    int indexPrevNotOf(const QByteArray &ba);
    int indexOf(const QByteArray &ba);

    void setFont(const QFont &font) { QAbstractScrollArea::setFont(font); adjust(); }
    int getCursorAddr(QPoint posa);

protected:
    virtual void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
    virtual void focusInEvent(QFocusEvent *) Q_DECL_OVERRIDE;
    virtual void resizeEvent(QResizeEvent *) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    virtual void keyPressEvent(QKeyEvent *) Q_DECL_OVERRIDE;

signals:
    void focused();

public slots:

private:
    void adjust();
    void cursorScroll();

    int m_bytesPerLine = 8;
    int m_baseAddr = 0;
    int m_addrCursor = 0;
    bool m_asciiArea = true;

    int m_charWidth;
    int m_charHeight;
    int m_selectPart;
    int m_marginGap;
    int m_addrLoc;
    int m_dataLine;
    int m_dataLoc;
    int m_asciiLine;
    int m_asciiLoc;

    int m_visibleRows;

    int m_lineAddrStart;
    int m_lineAddrEnd;

    QByteArray m_data;
    int m_size;
    int m_addrEnd;

    bool m_scrollable = false;          // fetch bytes from memory on scroll

    QRect m_cursor;
    int m_cursorHeight;
};

#endif
