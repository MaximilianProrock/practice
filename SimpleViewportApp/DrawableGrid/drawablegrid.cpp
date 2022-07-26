#include "drawablegrid.h"

DrawableGrid::DrawableGrid(double size, int nSegments, QColor color) :
    m_size(size),
    m_nSegments(nSegments),
    m_color(color)
{
}

void DrawableGrid::draw(QMatrix4x4 viewMatrix, QMatrix4x4 projectionMatrix)
{
    // using the old pipeline for simplicity
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(viewMatrix.data());
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(projectionMatrix.data());
    glColor3f(m_color.redF(), m_color.greenF(), m_color.blueF());
    glBegin(GL_LINES);
        const double segmentSize = m_size / m_nSegments;
        for (int segmentInd = 0; segmentInd < m_nSegments * 2 + 1; ++ segmentInd) {
            glVertex3f(-m_size + segmentInd * segmentSize, 0, -m_size);
            glVertex3f(-m_size + segmentInd * segmentSize, 0, m_size);
            glVertex3f(-m_size, 0, -m_size + segmentInd * segmentSize);
            glVertex3f(m_size, 0, -m_size + segmentInd * segmentSize);
        }
    glEnd();
}
