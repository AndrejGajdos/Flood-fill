#include "fill.h"

using namespace std;

/*****************************************************************************/

Error EdgeMap::Load(const string &path){

	ifstream streamFile;
    int length = 0;
    int seedFound = 0;
    int countChars = 0;
    int countLines = 0;
    m_correct = false;
    char a;
    int firstLineSize = 0;


    streamFile.open(path.c_str());

    if (streamFile.good()){

    	// size of file
    	streamFile.seekg (0, ios::end);
    	length = streamFile.tellg();
    	streamFile.seekg (0, ios::beg);

    	// reserve edgeMap
    	m_edgeMap.reserve(length);
    	m_edgeMap.clear();

    	for(int i = 0; i < length; i++){

    		a = streamFile.get();
    		countChars++;

    		if (a == PIXEL_BORDER) {
    			m_edgeMap.push_back(PIXEL_BORDER);
    		}

    		else if (a == PIXEL_SEED) {
    			if (seedFound > 1)
    			    return Error::E_MORESEEDS;
    			m_seed.setX(countChars-1);
    			m_seed.setY(countLines);
    			m_edgeMap.push_back(PIXEL_SEED);
    			seedFound++;
    		}

    		else if (a == PIXEL_BLANK) {
    			m_edgeMap.push_back(PIXEL_BLANK);
    		}

    		else if (a == '\n') {
    			if (firstLineSize == 0)
    				firstLineSize = countChars;

    			if(firstLineSize != countChars)
    			     return Error::E_SIZE;

    			countChars = 0;
    			countLines++;
    		}

    		else
    			return Error::E_INVALIDCHAR;
    	}

    	if (!seedFound)
    		return Error::E_NOSEED;

    	streamFile. close();
    }

    else
        return Error::E_CANTOPEN;


    m_mapSize.setX(firstLineSize-1);
    m_mapSize.setY(countLines);
    m_correct = true;
    return Error::E_OK;

}

/*****************************************************************************/

Error EdgeMap::Fill(ushort &area) {

    if(IsValid()){

    DynamicData nextSeeds;
    nextSeeds.push(m_seed);
    Point seedNextPoint;
    bool seedBelow;
    bool seedUnder;

    while(!nextSeeds.empty()) {

        nextSeeds.pop(seedNextPoint);

        seedBelow = false;
        seedUnder = false;

        if(seedNextPoint.getY() == 0 || seedNextPoint.getY() == m_mapSize.getY()-1)
            return Error::E_OUTOFMAP;

        // left side from seed
        for(int i = seedNextPoint.getX(); i >= 0; i--) {
            switch(m_edgeMap[getIndex(i,seedNextPoint.getY())]) {
                case PIXEL_BLANK:
                    if(i == 0 || i == m_mapSize.getX()-1)
                        return Error::E_OUTOFMAP;

                case PIXEL_SEED:

                    // conditions for the upper pixels
                	if (m_edgeMap[getIndex(i,seedNextPoint.getY()-1)] == PIXEL_BLANK){

                		if(!seedBelow) {
                			Point item(i,seedNextPoint.getY()-1);
                			nextSeeds.push(item);
                		}
                	    seedBelow = true;
                	 }

                	 if (m_edgeMap[getIndex(i,seedNextPoint.getY()-1)] == PIXEL_BORDER)
                	      seedBelow = false;

                	 // conditions for the under pixels
                	 if (m_edgeMap[getIndex(i,seedNextPoint.getY()+1)] == PIXEL_BLANK){

                	      if(!seedUnder) {
                	            Point item(i,seedNextPoint.getY()+1);
                	            nextSeeds.push(item);
                	      }
                	      seedUnder = true;
                	  }


                	 if (m_edgeMap[getIndex(i,seedNextPoint.getY()+1)] == PIXEL_BORDER)
                	      seedUnder = false;

                    m_edgeMap[getIndex(i,seedNextPoint.getY())] = PIXEL_FILLED;
                    area ++;
                    continue;

                case PIXEL_BORDER:
                    break;
            }
           break;
        }


        //right side from seed
        for(int i = seedNextPoint.getX()+1; i < m_mapSize.getX(); i++) {
            switch(m_edgeMap[getIndex(i,seedNextPoint.getY())]) {
                case PIXEL_BLANK:
                    if(i == 0 || i == m_mapSize.getX()-1)
                        return Error::E_OUTOFMAP;

                case PIXEL_SEED:

                	 // conditions for the upper pixels
                	 if (m_edgeMap[getIndex(i,seedNextPoint.getY()-1)] == PIXEL_BLANK){

                		 if(!seedBelow) {
                			 Point item(i,seedNextPoint.getY()-1);
                			 nextSeeds.push(item);
                		 }
                		 seedBelow = true;

                	 }

                	 if (m_edgeMap[getIndex(i,seedNextPoint.getY()-1)] == PIXEL_BORDER)
                		 seedBelow = false;


                	 // conditions for the under pixels
                    if (m_edgeMap[getIndex(i,seedNextPoint.getY()+1)] == PIXEL_BLANK){

                    	if(!seedUnder) {
                           Point item(i,seedNextPoint.getY()+1);
                           nextSeeds.push(item);
                    	}
                    	seedUnder = true;
                    }


                    if (m_edgeMap[getIndex(i,seedNextPoint.getY()+1)] == PIXEL_BORDER)
                    	seedUnder = false;

                    m_edgeMap[getIndex(i,seedNextPoint.getY())] = PIXEL_FILLED;
                    area ++;
                    continue;

                case PIXEL_BORDER:
                    break;
            }
            	break;
        }

    }

    return Error::E_OK;
    }

    return Error::E_NOTLOADED;
}

/*****************************************************************************/

Error EdgeMap::Print() const {
	if (IsValid()){
		for (int i = 0; i < m_mapSize.getY(); i++){
			for (int j = 0; j < m_mapSize.getX(); j++)
				cout << m_edgeMap[getIndex(j,i)];
			cout << endl;
		}

	}
	else
		return Error::E_NOTLOADED;

	return Error::E_OK;
}

/*****************************************************************************/

ushort EdgeMap::getIndex(ushort x, ushort y) const {
    return y * m_mapSize.getX() + x;
}

/*****************************************************************************/
