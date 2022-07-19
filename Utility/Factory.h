#pragma once
namespace Valzuroid {
	namespace Pinball {
		namespace Utility {
			template <typename T>
			class Factory
			{
			private:
				T** objectPointers;
				int count = 0;
				int maxSize = 10;
			protected:
				Factory(int maxSize = 100);
				T** GetAllObjects();
				int Count();
				T* GetNewObject();
				bool RemoveObject(T* object);
			public:
				void AddObject(T* object);
			};

			template <typename T>
			Factory<T>::Factory(int maxSize = 10)
			{
				this->maxSize = maxSize;
				objectPointers = new T * [maxSize];
			};

			template <typename T>
			void Factory<T>::AddObject(T* object)
			{
				if (count < maxSize)
				{
					objectPointers[count] = object;
				}
				else
				{
					T** tempPointer = new T * [maxSize];
					for (int i = 0; i < count; i++)
					{
						tempPointer[i] = objectPointers[i];
					}
					delete[] objectPointers;
					maxSize += 10;
					objectPointers = new T * [maxSize];
					for (int i = 0; i < count; i++)
					{
						objectPointers[i] = tempPointer[i];
					}
					objectPointers[count] = object;
					count++;
				}
				count++;
			};

			template <typename T>
			T** Factory<T>::GetAllObjects()
			{
				return objectPointers;
			}

			template <typename T>
			int Factory<T>::Count()
			{
				return count;
			}

			template <typename T>
			T* Factory<T>::GetNewObject()
			{
				T* newObject = new T();
				AddObject(newObject);
				return newObject;
			}

			template <typename T>
			bool Factory<T>::RemoveObject(T* object)
			{
				bool found = false;
				for (int i = 0; i < count; i++)
				{
					if (objectPointers[i] == object)
					{
						found = true;
						delete objectPointers[i];
					}

					if (found && i < count - 1)
					{
						objectPointers[i] = objectPointers[i + 1];
					}
				}
				return found;
			}
		}
	}
}