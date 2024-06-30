package com.forestsentry.alpha.services.impl;

import java.util.UUID;
import java.util.List;
import java.util.ArrayList;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;

import com.forestsentry.alpha.models.dtos.RecordDTO;
import com.forestsentry.alpha.models.entities.Record;
import com.forestsentry.alpha.repositories.RecordRepository;
import com.forestsentry.alpha.services.dec.RecordService;

@Service
public class RecordServiceImpl implements RecordService{

    @Autowired
    private RecordRepository recordRepository;

    @Override
    public Boolean save(RecordDTO dto) throws Exception{
        try{
            Record r = new Record(dto);
            recordRepository.save(r);
            return true;
        }
        catch(Exception e){
            throw e;
        }
    }

    @Override
    public Boolean delete(UUID id) throws Exception{
        try{
            recordRepository.deleteById(id);
            return true;
        }
        catch(Exception e){
            throw e;
        }
    }

    @Override
    public Record findLatest() throws Exception{
        try{
            return recordRepository.findFirstRecordOrderByTimestampAsc();
        }
        catch(Exception e){
            throw e;
        }
    }

    @Override
    public Record findById(UUID id) throws Exception{
        try{
            return recordRepository.findById(id).orElseThrow();
        }
        catch(Exception e){
            throw e;
        }
    }

    @Override
    public Page<Record> findByDeviceId(String id, Integer page, Integer size) throws Exception{
        try{
            Pageable pageable = PageRequest.of(page, size);
            return recordRepository.findAllByDeviceId(pageable);
        }
        catch(Exception e){
            throw e;
        }
    }

    @Override
    public List<Record> findLatestByDeviceId(List<String> ids) throws Exception{
        try{
            List<Record> l = new ArrayList<Record>();
            ids.forEach(id -> {
                l.add(recordRepository.findFirstRecordByDeviceIdOrderByTimestampAsc(id));
            });
            return l;
        }
        catch(Exception e){
            throw e;
        }
    }
    
}