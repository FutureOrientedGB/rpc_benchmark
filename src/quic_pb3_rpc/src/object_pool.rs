use std::collections::HashMap;
use std::sync::atomic::{AtomicPtr, Ordering};



pub struct ObjectPool<T> {
    objects: AtomicPtr<HashMap<String, T>>,
}

impl<T> ObjectPool<T> {
    fn new() -> Self {
        ObjectPool {
            objects: AtomicPtr::new(std::ptr::null_mut()),
        }
    }

    pub fn invoke<F1, F2, R>(&mut self, name: String, new_fn: F1, invoke_fn: F2) -> R
    where
        F1: FnOnce() -> T,
        F2: FnOnce(&mut T) -> R,
    {
        let objects_map_ptr = self.objects.load(Ordering::Acquire);
        let mut objects_map = unsafe { &mut *objects_map_ptr };

        if objects_map_ptr.is_null() {
            let new_map = Box::new(HashMap::new());
            let new_map_ptr = Box::into_raw(new_map);
            if self
                .objects
                .compare_exchange(objects_map_ptr, new_map_ptr, Ordering::Release, Ordering::Relaxed)
                .is_ok()
            {
                objects_map = unsafe { &mut *new_map_ptr };
            }
        }

        match objects_map.entry(name.clone()) {
            std::collections::hash_map::Entry::Occupied(mut occupied_entry) => {
                return invoke_fn(occupied_entry.get_mut());
            }
            std::collections::hash_map::Entry::Vacant(vacant_entry) => {
                let mut new_object = new_fn();
                let result = invoke_fn(&mut new_object);
                vacant_entry.insert(new_object);
                return result;
            }
        }
    }
}
