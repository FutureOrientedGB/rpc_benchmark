use std::collections::VecDeque;
use std::sync::atomic::{AtomicUsize, Ordering};



pub struct IdGenerator {
    name: String,
    counter: AtomicUsize,
    max_count: usize,
    cache: VecDeque<usize>,
}

impl IdGenerator {
    fn new(name: &str, max_count: usize) -> Self {
        IdGenerator {
            name: String::from(name),
            counter: AtomicUsize::new(0),
            max_count,
            cache: VecDeque::new(),
        }
    }

    fn name(&self) -> &String {
        &self.name
    }

    fn poll(&mut self) -> usize {
        if self.cache.is_empty() {
            self.fill();
        }
        self.cache.pop_front().unwrap()
    }

    fn fill(&mut self) {
        let current = self.counter.fetch_add(self.max_count, Ordering::Relaxed);
        let new_ids = (current..(current + self.max_count)).collect::<Vec<usize>>();
        self.cache.extend(new_ids);
    }
}
