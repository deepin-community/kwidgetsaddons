/*
    SPDX-FileCopyrightText: 2017 Henrik Fehlauer <rkflx@lab12.net>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "ksqueezedtextlabelautotest.h"

#include <KSqueezedTextLabel>

#include <QTest>

Q_DECLARE_METATYPE(Qt::TextElideMode)

namespace
{
KSqueezedTextLabel *createLabel(const QString &text = QStringLiteral("Squeeze me"))
{
    KSqueezedTextLabel *label = new KSqueezedTextLabel(QStringLiteral(""), nullptr);
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    // workaround for a QLabel bug, where the sizing for an empty label
    // is off, if it was initialized to an empty text.
    label->setText(QStringLiteral("x"));
    label->setText(text);
    label->show();
    return label;
}

void squeezeLabel(KSqueezedTextLabel *label, const int pixels = 10)
{
    label->resize(label->size().width() - pixels, label->size().height());
}

} // namespace

void KSqueezedTextLabelAutotest::testEmptyText()
{
    const QScopedPointer<KSqueezedTextLabel> label(createLabel(QString()));

    QVERIFY(label->text().isEmpty());
    QVERIFY(label->fullText().isEmpty());
    QVERIFY(label->toolTip().isEmpty());
    QVERIFY(!label->isSqueezed());
    QCOMPARE(label->width(), 0);
}

void KSqueezedTextLabelAutotest::testElisionOnResize_data()
{
    QTest::addColumn<QString>("text");
    QTest::addColumn<int>("squeezePixels");

    QTest::newRow("whitespace text") << "             " << 10;
    QTest::newRow("normal text") << "Squeeze me" << 10;
    QTest::newRow("rich text") << "<h1>Squeeze me!</h1>" << 80;
    // QTest::newRow("multiline text") << "Squeeze me,\nand\nme too.";
    // QTest::newRow("multiline rich text") << "<i>Squeeze</i> me,\n<b>and\nme</b> too.";
}

void KSqueezedTextLabelAutotest::testElisionOnResize()
{
    QFETCH(QString, text);
    QFETCH(int, squeezePixels);

    const QScopedPointer<KSqueezedTextLabel> label(createLabel(text));

    QVERIFY(label->text() == text);
    QVERIFY(label->fullText() == text);
    QVERIFY(label->toolTip().isEmpty());
    QVERIFY(!label->isSqueezed());

    squeezeLabel(label.data(), squeezePixels);

    QVERIFY(label->text() != text);
    QVERIFY(label->fullText() == text);
    QVERIFY(label->toolTip() == text);
    QVERIFY(label->isSqueezed());

    squeezeLabel(label.data(), -squeezePixels);

    QVERIFY(label->text() == text);
    QVERIFY(label->fullText() == text);
    QVERIFY(label->toolTip().isEmpty());
    QVERIFY(!label->isSqueezed());
}

void KSqueezedTextLabelAutotest::testElisionOnTextUpdate()
{
    const QScopedPointer<KSqueezedTextLabel> label(createLabel());

    QVERIFY(!label->isSqueezed());

    label->setText(label->text() + QStringLiteral("!!!"));

    QVERIFY(label->isSqueezed());
}

void KSqueezedTextLabelAutotest::testElideMode_data()
{
    QTest::addColumn<Qt::TextElideMode>("mode");
    QTest::addColumn<QChar>("prefix");
    QTest::addColumn<QChar>("infix");
    QTest::addColumn<QChar>("postfix");

    const QChar ellipsisChar(0x2026);
    const QChar a(QLatin1Char('a'));
    const QChar b(QLatin1Char('b'));
    const QChar c(QLatin1Char('c'));

    QTest::newRow("ElideLeft") << Qt::ElideLeft << ellipsisChar << b << c;
    QTest::newRow("ElideRight") << Qt::ElideRight << a << b << ellipsisChar;
    QTest::newRow("ElideMiddle") << Qt::ElideMiddle << a << ellipsisChar << c;
    QTest::newRow("ElideNone") << Qt::ElideNone << a << b << c;
}

void KSqueezedTextLabelAutotest::testElideMode()
{
    QFETCH(Qt::TextElideMode, mode);
    QFETCH(QChar, prefix);
    QFETCH(QChar, infix);
    QFETCH(QChar, postfix);

    // "abc" is not sufficient, because ellipsis might be wider than a single char
    const QScopedPointer<KSqueezedTextLabel> label(createLabel(QStringLiteral("aaabbbccc")));
    label->setTextElideMode(mode);
    squeezeLabel(label.data());
    const int infixPos = label->text().indexOf(infix);

    QVERIFY(label->isSqueezed() || mode == Qt::ElideNone);
    QVERIFY(label->text().startsWith(prefix));
    QVERIFY(0 < infixPos && infixPos < label->text().length() - 1);
    QVERIFY(label->text().endsWith(postfix));
}

void KSqueezedTextLabelAutotest::testSizeHints()
{
    const QScopedPointer<KSqueezedTextLabel> label(createLabel(QString()));

    QVERIFY(!label->isSqueezed());
    QCOMPARE(label->size().width(), 0);
    QCOMPARE(label->minimumSizeHint().width(), -1);
    QCOMPARE(label->sizeHint().width(), 0);

    label->adjustSize();

    QVERIFY(!label->isSqueezed());
    QCOMPARE(label->size().width(), 0);
    QCOMPARE(label->minimumSizeHint().width(), -1);
    QCOMPARE(label->sizeHint().width(), 0);

    const QString text = QStringLiteral("Squeeze me");
    const int labelWidth = label->fontMetrics().boundingRect(text).width(); // no chrome set
    label->setText(text);

    QVERIFY(label->isSqueezed());
    QCOMPARE(label->size().width(), 0);
    QCOMPARE(label->minimumSizeHint().width(), -1);
    QCOMPARE(label->sizeHint().width(), labelWidth);

    label->adjustSize();

    QVERIFY(!label->isSqueezed());
    QCOMPARE(label->size().width(), labelWidth);
    QCOMPARE(label->minimumSizeHint().width(), -1);
    QCOMPARE(label->sizeHint().width(), labelWidth + 2);

    const int indent = 40;
    label->setIndent(indent);
    label->adjustSize();

    QVERIFY(!label->isSqueezed());
    QCOMPARE(label->size().width(), labelWidth + indent);
    QCOMPARE(label->minimumSizeHint().width(), -1);
    QCOMPARE(label->sizeHint().width(), labelWidth + indent + 2);
}

void KSqueezedTextLabelAutotest::testClearing()
{
    const QScopedPointer<KSqueezedTextLabel> label(createLabel());
    squeezeLabel(label.data());

    QVERIFY(label->isSqueezed());

    label->clear();

    QVERIFY(label->text().isEmpty());
    QVERIFY(label->fullText().isEmpty());
    QEXPECT_FAIL("", "To fix: Reset tooltip in clear()", Continue);
    QVERIFY(label->toolTip().isEmpty());
    QVERIFY(!label->isSqueezed());
}

void KSqueezedTextLabelAutotest::testChrome_data()
{
    const QFontMetrics fm(KSqueezedTextLabel().fontMetrics());
    const int xWidth = fm.horizontalAdvance(QLatin1Char('x')) / 2;

    QTest::addColumn<QString>("attribute");
    QTest::addColumn<int>("amount");
    QTest::addColumn<int>("widthDifference");

    QTest::newRow("indent") << "indent" << 20 << 18;
    QTest::newRow("margin") << "margin" << 20 << 38;
    QTest::newRow("frame") << "lineWidth" << 20 << 38 + xWidth;
}

void KSqueezedTextLabelAutotest::testChrome()
{
    QFETCH(QString, attribute);
    QFETCH(int, amount);
    QFETCH(int, widthDifference);

    const QScopedPointer<KSqueezedTextLabel> label(createLabel());
    label->setFrameStyle(QFrame::Box);
    label->setLineWidth(0);
    const int oldWidth = label->width();

    QVERIFY(!label->isSqueezed());

    label->setProperty(attribute.toLatin1().data(), amount);

    QVERIFY(label->isSqueezed());

    label->adjustSize();

    QVERIFY(!label->isSqueezed());
    QCOMPARE(label->width(), oldWidth + widthDifference);
}

QTEST_MAIN(KSqueezedTextLabelAutotest)

// TODO
// currently untested, may need clarification/definition of correct behaviour:
// - multiline text
// - setWordWrap
// - setAlignment
// - setToolTip
// - context menu
// - Qt::TextInteractionFlags, keyboard/mouse interaction
// - linkHovered/linkActivated
// - setPixmap
