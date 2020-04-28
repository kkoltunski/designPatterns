#ifndef COMPOSITES_H
#define COMPOSITES_H

class composite {
private:
	virtual void compositeBehaviour() const = 0;
};

class specifiedComposite1 : public composite {
private:
	virtual void compositeBehaviour() const override {
		std::cout << "specifiedComposite1" << std::endl;
	}
};

class specifiedComposite2 : public composite {
private:
	virtual void compositeBehaviour() const override {
		std::cout << "specifiedComposite2" << std::endl;
	}
};

class compositeFactory : public factory<composite> {
public:
	virtual composite* factoryMethod(int _selector) override {
		composite* pToComposite{ nullptr };

		try {
			switch (_selector) {
			case 1:
				pToComposite = new specifiedComposite1;
				break;
			case 2:
				pToComposite = new specifiedComposite2;
				break;
			default:
				std::cout << "Unknown composite type" << std::endl;
				break;
			}

			if (pToComposite != nullptr) {
				pushToStorage(pToComposite);
			}
		}
		catch (std::bad_alloc& exception) {
			std::cout << exception.what() << std::endl;
			terminate();
		}
		
		return pToComposite;
	}
};
#endif //COMPOSITES_H