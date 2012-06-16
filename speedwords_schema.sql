CREATE TABLE dict (rap text, mot text, finrap text);
CREATE INDEX dictrap on dict (finrap);
CREATE INDEX dictmot on dict (mot);

